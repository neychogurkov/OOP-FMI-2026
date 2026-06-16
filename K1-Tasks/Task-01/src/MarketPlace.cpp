#include "MarketPlace.h"
#include <cstring>

void MarketPlace::copyFrom(const MarketPlace& other) {
    capacity = other.capacity;
    size = other.size;
    rent = other.rent;

    description = new char[strlen(other.description) + 1];
    strcpy(description, other.description);

    merchants = new Merchant * [capacity] {nullptr};
    for (unsigned i = 0; i < capacity; i++) {
        if (other.merchants[i]) {
            merchants[i] = new Merchant(*other.merchants[i]);
        }
    }
}

void MarketPlace::moveFrom(MarketPlace&& other) {
    capacity = other.capacity;
    other.capacity = 0;
    size = other.size;
    other.size = 0;
    rent = other.rent;
    other.rent = 0;

    description = other.description;
    other.description = nullptr;

    merchants = other.merchants;
    other.merchants = nullptr;
}

void MarketPlace::free() {
    for (unsigned i = 0; i < capacity; i++) {
        delete merchants[i];
    }

    delete[] merchants;
    delete[] description;
    merchants = nullptr;
    description = nullptr;
    capacity = 0;
    size = 0;
    rent = 0;
}

MarketPlace::MarketPlace(const char* description, unsigned capacity, double rent) : capacity(capacity), rent(rent), size(0) {
    if (!description) {
        this->description = new char[strlen("") + 1];
        strcpy(this->description, "");
    }
    else {
        this->description = new char[strlen(description) + 1];
        strcpy(this->description, description);
    }

    merchants = new Merchant * [capacity] {nullptr};
}

MarketPlace::MarketPlace(const MarketPlace& other) {
    copyFrom(other);
}

MarketPlace::MarketPlace(MarketPlace&& other) {
    moveFrom(std::move(other));
}

MarketPlace& MarketPlace::operator=(const MarketPlace& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

MarketPlace& MarketPlace::operator=(MarketPlace&& other) {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

MarketPlace::~MarketPlace() {
    free();
}

MarketPlace& MarketPlace::operator+=(const Merchant& merchant) {
    if (size == capacity) {
        delete merchants[size - 1];
        merchants[size - 1] = new Merchant(merchant);
        return *this;
    }

    for (unsigned i = 0; i < capacity; i++) {
        if (isFreeSlot(i)) {
            merchants[i] = new Merchant(merchant);
            size++;
            break;
        }
    }

    return *this;
}

MarketPlace& MarketPlace::operator-=(double minRevenue) {
    for (unsigned i = 0; i < capacity; i++) {
        if (merchants[i] && merchants[i]->getTotalIncome() < minRevenue) {
            delete merchants[i];
            merchants[i] = nullptr;
            size--;
        }
    }

    return *this;
}

MarketPlace& MarketPlace::operator()(unsigned days) {
    for (unsigned i = 0; i < capacity; i++) {
        if (merchants[i]) {
            for (unsigned j = 0; j < days; j++) {
                ++(*merchants[i]);
            }
        }
    }

    return *this;
}

MarketPlace::operator bool() const {
    return capacity > 0 && size * 2 >= capacity;
}

void MarketPlace::addAt(unsigned pos, const Merchant& merchant) {
    if (pos >= capacity) {
        return;
    }

    if (!merchants[pos]) {
        size++;
    }

    delete merchants[pos];
    merchants[pos] = new Merchant(merchant);
}

bool MarketPlace::isFreeSlot(unsigned pos) const {
    if (pos >= capacity) {
        return false;
    }

    return !merchants[pos];
}

unsigned MarketPlace::takenSlots() const {
    return size;
}

double MarketPlace::getProfit() const {
    double profit = 0;

    for (unsigned i = 0; i < capacity; i++) {
        if (merchants[i]) {
            profit += merchants[i]->getTotalIncome();
        }
    }

    return profit - rent * size;
}

double MarketPlace::averageProfit() const {
    if (size == 0) {
        return 0;
    }

    return getProfit() / size;
}

std::ostream& operator<<(std::ostream& os, const MarketPlace& market) {
    os << market.description << " (наем: " << market.rent << ")\n";

    for (unsigned i = 0; i < market.capacity; i++) {
        os << "[";
        if (market.merchants[i]) {
            os << market.merchants[i]->getId();
        }
        else {
            os << "*";
        }
        os << "] ";
    }

    return os;
}

bool operator==(const MarketPlace& lhs, const MarketPlace& rhs) {
    if (lhs.getProfit() == rhs.getProfit()) {
        return (double)lhs.size / lhs.capacity == (double)rhs.size / rhs.capacity;
    }

    return false;
}

std::partial_ordering operator<=>(const MarketPlace& lhs, const MarketPlace& rhs) {
    auto res = lhs.getProfit() <=> rhs.getProfit();

    if (res == std::partial_ordering::equivalent) {
        return (double)lhs.size / lhs.capacity <=> (double)rhs.size / rhs.capacity;
    }

    return res;
}

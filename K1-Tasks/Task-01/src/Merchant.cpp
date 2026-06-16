#include "Merchant.h"
#include <cstring>
#include <compare>

unsigned Merchant::idCount = 0;

void Merchant::setName(const char* name) {
    if (!name || strlen(name) >= MAX_NAME_LENGTH) {
        strcpy(this->name, "");
        return;
    }

    strcpy(this->name, name);
}

void Merchant::setTotalIncome(double totalIncome) {
    if (totalIncome < 0) {
        this->totalIncome = 0;
        return;
    }

    this->totalIncome = totalIncome;
}

void Merchant::setDailyIncome(double dailyIncome) {
    if (dailyIncome < 0) {
        this->dailyIncome = 0;
        return;
    }

    this->dailyIncome = dailyIncome;
}

Merchant::Merchant(const char* name, double totalIncome, double dailyIncome) : id(++idCount) {
    setName(name);
    setTotalIncome(totalIncome);
    setDailyIncome(dailyIncome);
}

double Merchant::getTotalIncome() const {
    return totalIncome;
}

unsigned Merchant::getId() const {
    return id;
}

Merchant& Merchant::operator++() {
    totalIncome += dailyIncome;
    return *this;
}

Merchant Merchant::operator++(int) {
    Merchant res = *this;
    totalIncome += dailyIncome;
    return res;
}

std::ostream& operator<<(std::ostream& os, const Merchant& merchant) {
    return os << merchant.name << " " << merchant.id << " " << merchant.totalIncome << " " << merchant.dailyIncome;
}

bool operator==(const Merchant& lhs, const Merchant& rhs) {
    return lhs.totalIncome == rhs.totalIncome;
}

std::partial_ordering operator<=>(const Merchant& lhs, const Merchant& rhs) {
    return lhs.totalIncome <=> rhs.totalIncome;
}

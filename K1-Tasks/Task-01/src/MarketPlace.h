#pragma once
#include <ostream>
#include "Merchant.h"

class MarketPlace {
private:
    Merchant** merchants;
    unsigned capacity;
    unsigned size;
    char* description;
    double rent;

    void copyFrom(const MarketPlace& other);
    void moveFrom(MarketPlace&& other);
    void free();

public:
    MarketPlace(const char* description, unsigned capacity, double rent);

    MarketPlace(const MarketPlace& other);
    MarketPlace(MarketPlace&& other);

    MarketPlace& operator=(const MarketPlace& other);
    MarketPlace& operator=(MarketPlace&& other);
    
    ~MarketPlace();

    MarketPlace& operator+=(const Merchant& merchant);
    MarketPlace& operator-=(double minRevenue);

    MarketPlace& operator()(unsigned days);
    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const MarketPlace& market);
    friend bool operator==(const MarketPlace& lhs, const MarketPlace& rhs);
    friend std::partial_ordering operator<=>(const MarketPlace& lhs, const MarketPlace& rhs);

    void addAt(unsigned pos, const Merchant& merchant);
    bool isFreeSlot(unsigned pos) const;
    unsigned takenSlots() const;
    double getProfit() const;
    double averageProfit() const;
};
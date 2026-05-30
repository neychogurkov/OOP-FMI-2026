#pragma once
#include <ostream>
#include <compare>

class Merchant {
private:
    static constexpr unsigned MAX_NAME_LENGTH = 1024;
    char name[MAX_NAME_LENGTH + 1];
    unsigned id;
    double totalIncome;
    double dailyIncome;

    static unsigned idCount;

    void setName(const char* name);
    void setTotalIncome(double totalIncome);
    void setDailyIncome(double dailyIncome);
public:
    Merchant(const char* name, double totalIncome, double dailyIncome);

    double getTotalIncome() const;
    unsigned getId() const;

    Merchant& operator++();
    Merchant operator++(int);

    friend std::ostream& operator<<(std::ostream& os, const Merchant& merchant);
    friend bool operator==(const Merchant& lhs, const Merchant& rhs);
    friend std::partial_ordering operator<=>(const Merchant& lhs, const Merchant& rhs);
};
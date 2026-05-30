#include <iostream>
#include "Merchant.h"
#include "MarketPlace.h"

int main() {
    Merchant m1("Иван", 1000, 200);
    Merchant m2("Мария", 1500, 300);
    Merchant m3("Петър", 800, 150);

    ++m1;
    m2++;

    std::cout << m1 << "\n";
    std::cout << m2 << "\n";
    std::cout << m3 << "\n";

    MarketPlace market("Централен пазар", 3, 400);

    market += m1;
    market += m2;
    market += m3;

    std::cout << market << "\n";
    //Централен пазар (наем: 400)
    // [1] [2] [3]

    std::cout << market.takenSlots() << "\n";
    std::cout << market.getProfit() << "\n";
    std::cout << market.averageProfit() << "\n";

    if (market) {
        std::cout << "Пазарът е жизнеспособен\n";
    }

    market(5);
    market(3)(2);

    MarketPlace market2("Южен пазар", 3, 350);
    market2 += m2;
    market2.addAt(2, m1);
    market2.addAt(1, m3);

    std::cout << market2 << "\n";
    std::cout << (market > market2 ? "Централен е по-добър" : "Южен е по-добър");
}
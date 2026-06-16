#include <iostream>
#include "SpecialCustomFunction.h"

int main() {
    int arr[5] = { 3,-4,0,10,40 };
    SpecialCustomFunction func(arr, 5, [](int num) -> int { return num * num + num; });

    std::cout << func(7) << std::endl << func(-4); // 56 16

    func--; // special values : 2, -5, -1, 9, 39

    std::cout << func(-5) << std::endl; // 25

    SpecialCustomFunction func2 = !func; // special values : -2, 5, 1, -9, -39

    std::cout << func2(5) << std::endl; // 25
}
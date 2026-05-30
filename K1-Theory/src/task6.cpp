#include <iostream>

struct Cmp {
    int v;
    auto operator<=>(const Cmp& o) const = default;
};

int main() {
    Cmp a{ 1 }, b{ 1 };
    std::cout << (a == b) << " " << (a < b) << "\n";  // 1 0
}
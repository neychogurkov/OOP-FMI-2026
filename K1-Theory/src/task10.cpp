#include <iostream>

class T {
public:
    T() {
        std::cout << "ctor\n";
    }
    T(const T&) {
        std::cout << "copy\n";
    }
    T(T&&) {
        std::cout << "move\n";
    }
};

T foo() {
    T t;
    return t;
}

int main() {
    T x = foo(); // ctor
}
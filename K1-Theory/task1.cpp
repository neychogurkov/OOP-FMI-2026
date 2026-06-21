#include <iostream>

class Person {
public:
    std::string name;
    Person(std::string n) : name(std::move(n)) {}

    void print() const {
        std::cout << name << std::endl;
    }
};

int main() {
    std::string n = "Alice";

    Person p1(n);
    Person p2(std::move(n)); // Тук копието в конструктора "краде" това n и n остава празно 

    std::cout << "n: " << n << std::endl; // n: 
    std::cout << "p1: "; p1.print();      // p1: Alice
    std::cout << "p2: "; p2.print();      // p2: Alice
}
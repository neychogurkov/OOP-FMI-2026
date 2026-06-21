#include <iostream>

class Item {
    int id;
public:
    Item(int id = -1) : id(id) {
        std::cout << "ctor " << id << "\n";
    }
    ~Item() {
        std::cout << "dtor " << id << "\n";
    }
};

int main() {
    Item arr[3] = { Item(0), Item(1), Item(2) };
    std::cout << "Inside main\n";
}
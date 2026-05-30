#include <iostream>

class MyString {
public:
    MyString() {
        std::cout << "default\n";
    }
    MyString(const MyString&) {
        std::cout << "copy\n";
    }
    MyString(MyString&&) {
        std::cout << "move\n";
    }
};

int main() {
    MyString a; // default
    MyString b = a; // copy
    MyString c = std::move(b); // move
}
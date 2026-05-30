#include <iostream>

class MyClass {
public:
    MyClass() = default;
    MyClass(const MyClass&) = delete;
    MyClass& operator=(const MyClass&) = delete;
};

int main() {
    MyClass a;
    std::cout << "before\n";
    //MyClass b = a; // Тук има грешка при компилация, защото сме забранили copy ctor-а, а се пробваме да го ползваме. Ако махнем delete на copy ctor-а ще работи. Ако махнем delete на operator= на класа отново няма да работи, защото тук се вика copy ctor.
    std::cout << "done\n";
}
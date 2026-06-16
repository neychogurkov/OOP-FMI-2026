#include <iostream>

class A {
public:
    A() {
        std::cout << "A()\n";
    }
    A(const A&) {
        std::cout << "A(copy)\n";
    }
};

void foo(A a) {
    std::cout << "in foo\n";
}

int main() {
    A a;     //А()
    foo(a);  //A(copy) \n in foo
}
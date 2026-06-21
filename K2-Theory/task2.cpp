#include <iostream>
#include <stdexcept>

using namespace std;

struct E : runtime_error {
    E(const string& msg)
        : runtime_error(msg) {}
};

struct F : E {
    F(const string& msg)
        : E(msg) {}
};

struct A {
    A() { cout << "A "; }

    virtual ~A() {
        cout << "~A ";
    }
};

struct B : virtual A {
    B() { cout << "B "; }

    ~B() override {
        cout << "~B ";
    }
};

struct C : virtual A {
    C() {
        cout << "C ";
        throw F("fail");
    }

    ~C() override {
        cout << "~C ";
    }
};

struct D : B, C {
    D() {
        cout << "D ";
    }

    ~D() override {
        cout << "~D ";
    }
};

int main() {
    try {
        D d;
        cout << "ok ";
    }
    catch (const E& e) {
        cout << e.what() << ' ';
    }
}
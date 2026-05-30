#include <iostream>

class A {
    int number = 5;
public:
    A(int i) : number(i) {}
};

int main() {
    //A* arr = new A[3]; // грешка при компилация, защото A няма default ctor
    for (int i = 0; i < 3; i++) {
        //std::cout << arr[i].number; // грешка при компилация, защото number е private
    }
    //delete[] arr;
}
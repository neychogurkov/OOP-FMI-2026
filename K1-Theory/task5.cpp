#include <iostream>

class Engine {
public:
    Engine() {
        std::cout << "Engine\n";;
    }
};

class Car {
    Engine e;

public:
    Car() {
        std::cout << "Car\n";
    }
};

int main() {
    Car c;  //Engine \n Car
}
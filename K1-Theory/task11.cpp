#include <iostream>

class Resource {
    int* data;
public:
    Resource() {
        data = new int(10);
        std::cout << "Constructor\n";
    }
    Resource(const Resource& other) {
        data = new int(*other.data);
        std::cout << "Copy constructor\n";
    }
    Resource(Resource&& other) {
        data = other.data;
        other.data = nullptr;
        std::cout << "Move constructor\n";
    }
    ~Resource() {
        std::cout << "Destructor\n";
        delete data;
    }
};

int main() {
    Resource a;
    Resource b = a;
}
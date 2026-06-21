#include <iostream>
#include <vector>

class Student {
public:
    std::string name;

    Student(std::string n) : name(std::move(n)) {
        std::cout << "ctor " << name << "\n";
    }

    Student(const Student& o) : name(o.name) {
        std::cout << "copy " << name << "\n";
    }
};

int main() {
    std::vector<Student> v;
    v.emplace_back("Ivan");
    v.push_back(v[0]);

}
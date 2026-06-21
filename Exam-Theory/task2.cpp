#include <iostream>
#include <vector>
class Animal {
    //protected:
    std::string name;

public:
    Animal(const std::string& n) : name(n) {}

    /*virtual*/ ~Animal() {
        std::cout << "Animal destroyed: " << name << "\n";
    }

    /*virtual*/ void speak() /*const*/ {
        std::cout << name << " makes a generic sound\n";
    }

    std::string getName() const {
        return name;
    }
};


class Dog : public Animal {

    int loyalty;

public:
    Dog(const std::string& n, int l)
        : Animal(n), loyalty(l) {
    }

    void speak() /*const override*/ {
        std::cout << name << " barks with loyalty " << loyalty << "\n";
    }

    void fetch() /*const*/ {
        std::cout << name << " is fetching\n";
    }
};

class Cat : public Animal {
    int mood;

public:
    Cat(const std::string& n, int m)
        : Animal(n), mood(m) {
    }

    void speak() /*const override*/ {
        std::cout << name << " meows with mood " << mood << "\n";
    }

    void purr() /*const*/ {
        std::cout << name << " is purring\n";
    }
};


void makeAnimalsSpeak(/*const*/ std::vector<Animal*>/*&*/ animals) {
    for (/*const*/ auto/*&*/ a : animals) {
        a->speak();
    }
}

int main() {
    std::vector<Animal*> animals;

    animals.push_back(new Dog("Rex", 10));
    animals.push_back(new Cat("Misty", 3));
    animals.push_back(new Dog("Bobby", 7));

    makeAnimalsSpeak(animals);

    for (/*const*/ auto/*&*/ a : animals) {
        if (a->getName() == "Rex") {
            /*dynamic_cast*/static_cast<Dog*>(a)->fetch();
        }

        if (a->getName() == "Misty") {
            /*dynamic_cast*/static_cast<Cat*>(a)->purr();
        }
    }

    for (/*const*/ auto/*&*/ a : animals) {
        delete a;
    }

    return 0;
}
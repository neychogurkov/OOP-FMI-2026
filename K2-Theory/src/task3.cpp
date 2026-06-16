#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Person {
    string name;

    Person(string n)
        : name(move(n)) {
        cout << "P(" << name << ") ";
    }

    Person(const Person& o)
        : name(o.name) {
        cout << "CP(" << name << ") ";
    }

    virtual ~Person() {
        cout << "~P(" << name << ") ";
    }

    virtual void info() const {
        cout << "person ";
    }
};

struct Student : Person {
    int year;

    Student(string n, int y)
        : Person(move(n)), year(y) {
        cout << "S(" << year << ") ";
    }

    Student(const Student& o)
        : Person(o), year(o.year) {
        cout << "CS(" << year << ") ";
    }

    ~Student() override {
        cout << "~S(" << year << ") ";
    }

    void info() const override {
        cout << "student ";
    }
};

struct Teacher : Person {
    Teacher(string n)
        : Person(move(n)) {
        cout << "T ";
    }

    void info() const override {
        cout << "teacher ";
    }
};

void by_value(Person p) {
    p.info();
}

int main() {
    unique_ptr<Person> a =
        make_unique<Student>("Ana", 2);

    unique_ptr<Person> b =
        make_unique<Teacher>("Bob");

    a->info();
    b->info();

    by_value(*a);

    Person c = *a;
    c.info();
}
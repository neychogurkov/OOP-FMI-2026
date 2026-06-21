#include <string>
#include <iostream>

enum Faculty {
    FMI,
    TU,
    UNWE
};

class Student {
public:
    static int count;

    Student(const std::string& name, int age) {
        this->name = name;
        this->age = age;
        count++;
    }

    Student(const Student& other) {
        name = other.name;
        age = other.age;
        count++;
    }

    ~Student() {
        count--;
    }

    std::string getName() const {
        return name;
    }

    void setAge(int age) {
        if (age > 0)
            this->age = age;
    }

    void print() const {
        printCounter++;
        std::cout << name << " " << age << '\n';
    }

    static Student createTemp() {
        Student s("Temp", 18);
        return s;
    }

private:
    std::string name;
    int age{};
    mutable int printCounter{};
};

int Student::count = 0;

Student& getStudent() { //should return Student
    Student s("Local", 22);
    return s;
}

int main() {
    Student a = Student::createTemp();
    Student b = a;

    Student& r = getStudent(); // Student r

    Student* arr = new Student[2]{
        Student("A", 20),
        Student("B", 21)
    };

    delete/*[]*/ arr;

    Student c("Ivan", -5);
    c.setAge(-10);

    const Student d("Const", 30);
    d.print();

    std::cout << Student::count << '\n';

    Faculty f = FMI;

    return 0;
}
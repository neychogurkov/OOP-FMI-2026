#include <string>
#include <iostream>
#include <vector>
#include <variant>
#include <algorithm>

class Student {
public:
    std::string name;
    int grade;

    Student(std::string n, int g)
        : name(n), grade(g) {
    }

    bool operator==(const Student& other) const {
        return grade == other.grade;
    }

    auto operator<=>(const Student&) const = default;
};

template<typename T>
class Box {
    T* data;

public:
    Box(T value) {
        data = new T(value);
    }

    //Rule of Five

    ~Box() {
        delete data;
    }

    T& get() {
        return *data;
    }
};

class Course {
    std::vector<Student*> students;

public:
    void addStudent(Student& s) {
        students.push_back(&s);
    }

    void print() const {
        for (auto s : students) { //const auto& s
            std::cout << s->name << '\n';
        }
    }
};

int main() {

    std::vector<Student> students;

    students.push_back(Student("Ivan", 5));
    students.push_back(Student("Maria", 6));

    Course course;

    course.addStudent(students[0]);
    course.addStudent(students[1]);

    students.push_back(Student("Georgi", 4));

    course.print(); //possible dangling pointers after push_back realloc

    auto avg = 0; // double

    for (auto s : students) //const auto& s
        avg += s.grade;

    std::cout << "Average: " << avg / students.size() << '\n'; //possible division by zero

    Box<int> b1(10);
    Box<int> b2 = b1; //shallow copy, double delete

    std::variant<int, std::string> contact = 42;

    std::cout << std::get<std::string>(contact); // bad_variant_access exception

    auto best = *std::max_element(students.begin(), students.end()); //inconsistent <=> and ==

    std::cout << best.name << '\n';
}
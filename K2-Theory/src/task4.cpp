#include <iostream>
#include <vector>

template<typename T>
struct Printer {
    static void print(const T&) {
        std::cout << "GEN ";
    }
};

template<>
struct Printer<int> {
    static void print(const int&) {
        std::cout << "INT ";
    }
};

template<typename T>
struct Printer<std::vector<T>> {
    static void print(const std::vector<T>& v) {
        std::cout << "VEC{ ";

        for (const auto& x : v) {
            Printer<T>::print(x);
        }

        std::cout << "} ";
    }
};

template<>
struct Printer<std::vector<int>> {
    static void print(const std::vector<int>& v) {
        std::cout << "VEC_INT{ ";

        for (const auto& x : v) {
            Printer<int>::print(x);
        }

        std::cout << "} ";
    }
};

int main() {
    Printer<double>::print(3.14);
    Printer<int>::print(5);

    std::vector<int> vi = {1, 2};
    std::vector<double> vd = {1.1, 2.2};

    Printer<std::vector<int>>::print(vi);
    Printer<std::vector<double>>::print(vd);

    std::cout << std::endl;
}
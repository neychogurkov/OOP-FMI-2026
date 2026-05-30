#include <iostream>

class Log {
    std::string name;
public:
    Log(std::string n) : name(std::move(n)) {
        std::cout << "open" << "\n";
        // Следното би ни дало празен ред:
        // std:: cout << n << "\n";
    }
    ~Log() {
        std::cout << "close " << "\n";
    }

    void info(const std::string& m) {
        std::cout << name << ": " << m << "\n";
    }
};

int main() {
    {
        Log l("app"); // open
        l.info("hi"); // app: hi
    }                 // close

    std::cout << "end\n"; // end
}
#pragma once
#include <string>
#include <iostream>
#include <compare>

class Patient {
private:
    std::string name;
    std::string egn;
    std::string diagnosis;
    unsigned roomNumber;

public:
    Patient(const std::string& name, const std::string& egn, const std::string& diagnosis, unsigned roomNumber);

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
    friend auto operator<=>(const Patient& lhs, const Patient& rhs);

    const std::string& getEgn() const;
    const std::string& getName() const;
    const std::string& getDiagnosis() const;

    void setDiagnosis(const std::string& diagnosis);
};
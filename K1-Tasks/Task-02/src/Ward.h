#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Patient.h"

class Ward {
private:
    std::string name;
    std::vector<std::shared_ptr<Patient>> patients;

public:
    Ward(const std::string& name);

    const std::string& getName() const;
    size_t getPatientsCount() const;

    void addPatient(const std::shared_ptr<Patient>& patient);
    void removePatient(const std::string& egn);
    Patient* findPatient(const std::string& egn) const;

    Ward& operator()(const std::string& egn, const std::string& diagnosis);
    explicit operator bool() const;
    friend std::ostream& operator<<(std::ostream&, const Ward& ward);
};
#include "Ward.h"

Ward::Ward(const std::string& name) : name(name) {
}

const std::string& Ward::getName() const {
    return name;
}

size_t Ward::getPatientsCount() const {
    return patients.size();
}

void Ward::addPatient(const std::shared_ptr<Patient>& patient) {
    if (findPatient(patient->getEgn()) != nullptr) {
        return;
    }

    patients.push_back(patient);
}

void Ward::removePatient(const std::string& egn) {
    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i]->getEgn() == egn) {
            patients.erase(patients.begin() + i);
            return;
        }
    }
}

Patient* Ward::findPatient(const std::string& egn) const {
    for (const auto& patient : patients) {
        if (patient->getEgn() == egn) {
            return patient.get();
        }
    }

    return nullptr;
}

Ward& Ward::operator()(const std::string& egn, const std::string& diagnosis) {
    Patient* patient = findPatient(egn);

    if (patient) {
        patient->setDiagnosis(diagnosis);
    }

    return *this;
}

Ward::operator bool() const {
    return patients.size() >= 1;
}

std::ostream& operator<<(std::ostream& os, const Ward& ward) {
    os << "Ward: " << ward.name << "\n";

    for (size_t i = 0; i < ward.patients.size(); i++) {
        os << *ward.patients[i];
    }

    return os;
}

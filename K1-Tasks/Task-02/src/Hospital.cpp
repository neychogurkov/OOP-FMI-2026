#include "Hospital.h"

Hospital& Hospital::getInstance() {
    static Hospital hospital;
    return hospital;
}

void Hospital::addWard(const std::string& name) {
    wards.emplace_back(name);
}

void Hospital::removeWard(const std::string& name) {
    for (size_t i = 0; i < wards.size(); i++) {
        if (wards[i].getName() == name) {
            wards.erase(wards.begin() + i);
            return;
        }
    }
}

Ward& Hospital::operator[](const std::string& name) {
    for (auto& w : wards) {
        if (w.getName() == name) {
            return w;
        }
    }

    static Ward dummy("Unknown");
    return dummy;
}

const Ward& Hospital::operator[](const std::string& name) const {
    for (const auto& w : wards) {
        if (w.getName() == name) {
            return w;
        }
    }

    static const Ward dummy("Unknown");
    return dummy;
}

std::vector<Ward> Hospital::findPatientsInWards(const std::string& egn) {
    std::vector<Ward> result;

    for (const auto& ward : wards) {
        if (ward.findPatient(egn)) {
            result.push_back(ward);
        }
    }

    return result;
}

size_t Hospital::countPatientWards(const std::string& egn) {
    size_t count = 0;

    for (const auto& ward : wards) {
        if (ward.findPatient(egn)) {
            count++;
        }
    }

    return count;
}

Hospital::operator bool() const {
    size_t totalPatients = 0;

    for (const auto& ward : wards) {
        totalPatients += ward.getPatientsCount();
    }

    double averagePatients = (double)totalPatients / wards.size();

    return averagePatients > 20;
}

std::ostream& operator<<(std::ostream& os, const Hospital& hospital) {
    os << hospital.name << "\n";

    for (const auto& ward : hospital.wards) {
        os << ward;
    }

    return os;
}

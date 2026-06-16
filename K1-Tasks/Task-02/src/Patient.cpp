#include <iostream>
#include "Patient.h"
#include <compare>

Patient::Patient(const std::string& name, const std::string& egn, const std::string& diagnosis, unsigned roomNumber) : name(name), egn(egn), diagnosis(diagnosis), roomNumber(roomNumber) {
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << "Name: " << patient.name << ", "
	    << "EGN: " << patient.egn << ", "
		<< "Diagnosis: " << patient.diagnosis << ", "
		<< "Room Number: " << patient.roomNumber << "\n";
	return os;
}

auto operator<=>(const Patient& lhs, const Patient& rhs) {
    return lhs.egn <=> rhs.egn;
}

const std::string& Patient::getEgn() const {
    return egn;
}

const std::string& Patient::getName() const {
    return name;
}

const std::string& Patient::getDiagnosis() const {
    return diagnosis;
}

void Patient::setDiagnosis(const std::string& diagnosis) {
    this->diagnosis = diagnosis;
}

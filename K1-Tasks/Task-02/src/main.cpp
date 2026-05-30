#include <iostream>
#include <vector>
#include <string>
#include "Patient.h"
#include "Ward.h"
#include "Hospital.h"
#include <memory>

int main() {
    Hospital& hospital = Hospital::getInstance();

    std::string cardiology = "Кардиология";
    std::string neurology = "Неврология";
    hospital.addWard(cardiology);
    hospital.addWard(neurology);

    auto patient = std::make_shared<Patient>("Ivan", "1231321", "Good", 120);

    hospital[cardiology].addPatient(patient);
    hospital[neurology].addPatient(patient);

    hospital[cardiology]("1231321", "Хипертония")("1231321", "Аритмия");

    std::cout << hospital << "\n";
    std::cout << "В колко отделения е пациентът: "
        << hospital.countPatientWards("1231321") << "\n";

    auto wards = hospital.findPatientsInWards("1231321");
    for (const auto& w : wards) {
        std::cout << "Намерен в: " << w.getName() << "\n";
    }

    if (!hospital) {
        std::cout << "Болницата не е пренаселена\n";
    }
}
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Ward.h"

class Hospital {
private:
    std::string name;
    std::vector<Ward> wards;
    Hospital() = default;
public:
    Hospital(const Hospital&) = delete;
    Hospital& operator=(const Hospital&) = delete;

    static Hospital& getInstance();

    void addWard(const std::string& name);
    void removeWard(const std::string& name);
    
    Ward& operator[](const std::string& name);
    const Ward& operator[](const std::string& name) const;
    
    std::vector<Ward> findPatientsInWards(const std::string& egn);
    size_t countPatientWards(const std::string& egn);

    friend std::ostream& operator<<(std::ostream& os, const Hospital& hospital);
    explicit operator bool() const;
};
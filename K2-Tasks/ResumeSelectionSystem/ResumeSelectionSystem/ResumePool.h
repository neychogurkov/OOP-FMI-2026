#pragma once
#include "Resume.h"
#include "Pool.hpp"
#include <optional>
#include <string>
#include <vector>

class ResumePool : public Pool<Resume>{
	
public:
	std::optional<Resume> findByEmail(const std::string& email) const;

	std::vector<Resume> filterBySkill(const std::string& skill) const;

	double averageSalary() const;
};


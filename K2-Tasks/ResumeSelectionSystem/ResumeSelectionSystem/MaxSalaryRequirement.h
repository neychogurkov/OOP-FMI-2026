#pragma once
#include "Requirement.h"
#include <string>
#include <optional>
#include "Resume.h"
#include <memory>

class MaxSalaryRequirement : public Requirement {
private:
	double maxSalary;

public:
	MaxSalaryRequirement(double maxSalary);

	std::optional<std::string> check(const Resume& resume) const override;

	std::unique_ptr<Requirement> clone() const override;
};


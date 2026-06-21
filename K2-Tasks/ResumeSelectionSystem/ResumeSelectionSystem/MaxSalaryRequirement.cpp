#include "MaxSalaryRequirement.h"
#include <stdexcept>

MaxSalaryRequirement::MaxSalaryRequirement(double maxSalary) : maxSalary(maxSalary) {
	if (maxSalary < 0) {
		throw std::invalid_argument("Maximum salary must be a positive number.");
	}
	
}

std::optional<std::string> MaxSalaryRequirement::check(const Resume& resume) const {
	if (maxSalary < resume.getDesiredSalary()) {
		return "Desired salary exceeds the max salary";
	}

	return std::nullopt;
}

std::unique_ptr<Requirement> MaxSalaryRequirement::clone() const {
	return std::make_unique < MaxSalaryRequirement>(*this);
}

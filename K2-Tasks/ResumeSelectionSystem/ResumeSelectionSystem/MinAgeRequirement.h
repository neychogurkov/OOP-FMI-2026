#pragma once
#include "Requirement.h"
#include "Resume.h"
#include <string>
#include <optional>
#include <memory>

class MinAgeRequirement : public Requirement {
private:
	unsigned minAge;

public:
	MinAgeRequirement(unsigned minAge);

	std::optional<std::string> check(const Resume& resume) const override;

	std::unique_ptr<Requirement> clone() const override;
};


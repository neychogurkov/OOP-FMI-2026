#pragma once
#include <string>
#include <optional>
#include "Requirement.h"
#include "Resume.h"
#include <memory>

class MinExperienceRequirement : public Requirement {
private:
	unsigned minExperience;

public:
	MinExperienceRequirement(unsigned minExperience);

	std::optional<std::string> check(const Resume& resume) const override;

	std::unique_ptr<Requirement> clone() const override;
};


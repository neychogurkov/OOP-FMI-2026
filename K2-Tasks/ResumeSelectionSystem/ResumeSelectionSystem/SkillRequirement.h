#pragma once
#include <string>
#include "Requirement.h"
#include <optional>
#include "Resume.h"
#include <memory>

class SkillRequirement : public Requirement {
private:
	std::string skill;

public:
	SkillRequirement(const std::string& skill);

	std::optional<std::string> check(const Resume& resume) const override;

	std::unique_ptr<Requirement> clone() const override;
};


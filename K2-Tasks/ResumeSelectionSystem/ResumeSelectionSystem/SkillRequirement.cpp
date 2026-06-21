#include "SkillRequirement.h"
#include <string>
#include "Resume.h"
#include <optional>
#include "Requirement.h"
#include <memory>
#include <algorithm>

SkillRequirement::SkillRequirement(const std::string& skill) : skill(skill){
}

std::optional<std::string> SkillRequirement::check(const Resume& resume) const {
	auto it = std::find(resume.getSkills().begin(), resume.getSkills().end(), skill);

	if (it == resume.getSkills().end()) {
		return "Missing skill: " + skill;
	}

	return std::nullopt;
}

std::unique_ptr<Requirement> SkillRequirement::clone() const {
	return std::make_unique<SkillRequirement>(*this);
}

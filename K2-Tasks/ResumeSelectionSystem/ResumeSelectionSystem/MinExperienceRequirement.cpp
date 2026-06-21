#include "MinExperienceRequirement.h"
#include <memory>
#include "Requirement.h"
#include <optional>
#include "Resume.h"
#include <string>

MinExperienceRequirement::MinExperienceRequirement(unsigned minExperience) :minExperience(minExperience) {

}

std::optional<std::string> MinExperienceRequirement::check(const Resume& resume) const {
	if (minExperience > resume.getYearsOfExperience()) {
		return "Not enough experience (" + std::to_string(resume.getYearsOfExperience()) + " < " + std::to_string(minExperience) + " years)";
	}

	return std::nullopt;
}

std::unique_ptr<Requirement> MinExperienceRequirement::clone() const {
	return std::make_unique<MinExperienceRequirement>(*this);
}

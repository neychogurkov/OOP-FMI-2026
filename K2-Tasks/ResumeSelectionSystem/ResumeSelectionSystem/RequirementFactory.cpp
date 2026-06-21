#include "RequirementFactory.h"
#include <memory>
#include <string>
#include "Requirement.h"
#include <utility>
#include "MinExperienceRequirement.h"
#include "SkillRequirement.h"
#include "MaxSalaryRequirement.h"
#include "MinAgeRequirement.h"
#include <stdexcept>

std::unique_ptr<Requirement> RequirementFactory::create(const std::pair<std::string, std::string>& input) {
	if (input.first == "min_experience") {
		return std::make_unique<MinExperienceRequirement>(std::stoi(input.second));
	}
	if (input.first == "skill") {
		return std::make_unique<SkillRequirement>(input.second);
	}
	if (input.first == "max_salary") {
		return std::make_unique<MaxSalaryRequirement>(std::stod(input.second));
	}
	if (input.first == "min_age") {
		return std::make_unique<MinAgeRequirement>(std::stoi(input.second));
	}

	throw std::invalid_argument("No such requirement.");
}

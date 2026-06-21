#include "MinAgeRequirement.h"
#include "Requirement.h"
#include <memory>
#include <string>
#include <optional>
#include "Resume.h"

MinAgeRequirement::MinAgeRequirement(unsigned minAge) :minAge(minAge) {
}

std::optional<std::string> MinAgeRequirement::check(const Resume& resume) const {
	if (minAge > resume.getAge()) {
		return "The candidate is under the minimum age of " + std::to_string(minAge);
	}

	return std::nullopt;
}

std::unique_ptr<Requirement> MinAgeRequirement::clone() const {
	return std::make_unique<MinAgeRequirement>(*this);
}

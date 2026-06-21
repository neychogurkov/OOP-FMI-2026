#pragma once
#include "Requirement.h"
#include <string>
#include <memory>
#include <utility>


class RequirementFactory {
public:
	RequirementFactory() = delete;

	static std::unique_ptr<Requirement> create(const std::pair<std::string, std::string>& input);
};


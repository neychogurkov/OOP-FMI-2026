#pragma once
#include <optional>
#include <string>
#include "Resume.h"
#include <memory>
class Requirement {
public:
	virtual std::optional<std::string> check(const Resume& resume) const = 0;

	virtual std::unique_ptr<Requirement> clone() const = 0;

	virtual ~Requirement() = default;
};


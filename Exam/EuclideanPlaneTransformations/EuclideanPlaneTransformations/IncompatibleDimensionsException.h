#pragma once
#include <stdexcept>

class IncompatibleDimensionsException : public std::logic_error
{
	std::string message;

public:
	explicit IncompatibleDimensionsException(const std::string& message);

	const char* what() const noexcept override;
};


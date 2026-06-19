#pragma once
#include <string>
#include <stdexcept>

class TransformationException : public std::logic_error
{
	std::string message;

public:
	explicit TransformationException(const std::string& message);

	const char* what() const noexcept override;
};

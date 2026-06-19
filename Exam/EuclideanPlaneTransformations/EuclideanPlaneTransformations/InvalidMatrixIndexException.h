#pragma once
#include <string>
#include <stdexcept>

class InvalidMatrixIndexException : public std::logic_error
{
	std::string message;

public:
	explicit InvalidMatrixIndexException(const std::string& message);

	const char* what() const noexcept override;
};


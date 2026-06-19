#include "InvalidMatrixIndexException.h"

InvalidMatrixIndexException::InvalidMatrixIndexException(const std::string& message) : logic_error(message), message(message)
{
}

const char* InvalidMatrixIndexException::what() const noexcept
{
	return message.c_str();
}

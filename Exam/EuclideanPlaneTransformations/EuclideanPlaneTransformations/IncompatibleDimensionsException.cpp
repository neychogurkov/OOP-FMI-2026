#include "IncompatibleDimensionsException.h"

IncompatibleDimensionsException::IncompatibleDimensionsException(const std::string& message) : logic_error(message), message(message)
{
}

const char* IncompatibleDimensionsException::what() const noexcept
{
    return message.c_str();
}

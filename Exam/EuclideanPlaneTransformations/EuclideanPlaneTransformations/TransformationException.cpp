#include "TransformationException.h"

TransformationException::TransformationException(const std::string& message) : std::logic_error(message), message(message)
{
}

const char* TransformationException::what() const noexcept
{
    return message.c_str();
}

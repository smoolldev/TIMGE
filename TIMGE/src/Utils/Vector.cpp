#include "TIMGE/Utils/Vector.hpp"

#include <format>

namespace TIMGE
{
    VectorException::VectorException(std::string message)
     : Exception(std::format("Vector: {}", message))
    {}
}

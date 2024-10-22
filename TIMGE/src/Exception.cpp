#include "TIMGE/Exception.hpp"

#include <string>

namespace TIMGE
{
    Exception::Exception(std::string message)
     : mWhat{message}
    {}

    [[nodiscard]] const std::string& Exception::What() const {
        return mWhat;
    }

    [[nodiscard]] const std::string& Exception::operator()() const {
        return mWhat;
    }
}

#include "TIMGE/Exception.hpp"

#include <string_view>
#include <format>

namespace TIMGE
{
    Exception::Exception()
    {}

    Exception::Exception(std::string_view message)
     : mWhat{message}
    {}

    Exception::Exception(std::string_view message, std::filesystem::path filepath, int line)
     : mWhat(std::format("{}: {} - {}", filepath.c_str(), line, message))
    {}

    [[nodiscard]] const std::string_view& Exception::What() const {
        return mWhat;
    }

    [[nodiscard]] const std::string_view& Exception::operator()() const {
        return mWhat;
    }
}

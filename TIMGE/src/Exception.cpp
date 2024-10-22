#include "TIMGE/Exception.hpp"

#include <format>
#include <source_location>
#include <string>

namespace TIMGE
{
    Exception::Exception()
    {}

    Exception::Exception(std::string message, const std::source_location location)
    {
        std::string filename{location.file_name()};
        char pathSeparator = filename.find('/') == filename.end() - filename.begin() ? '\\' : '/';
        filename = filename.substr(filename.find_last_of(pathSeparator) + 1);
        mWhat = std::format("{} @ {}: {}", filename, location.line(), message);
    }

    [[nodiscard]] const std::string& Exception::What() const {
        return mWhat;
    }

    [[nodiscard]] const std::string& Exception::operator()() const {
        return mWhat;
    }
}

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <filesystem>
#include <string_view>

#define MAKE_EXCEPTION_MESSAGE(message) \
	std::format("{}: {} - {}", __FILE__, __LINE__, message)

namespace TIMGE
{
	class Exception
	{
		public:
			Exception();
			Exception(std::string_view message);
			Exception(std::string_view message, std::filesystem::path filepath, int line);

			[[nodiscard]] virtual const std::string_view& What() const;

			[[nodiscard]] virtual const std::string_view& operator()() const;
		private:
			std::string_view mWhat;
	};
}

#endif // EXCEPTION_HPP

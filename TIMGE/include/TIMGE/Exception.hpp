#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <source_location>
#include <string>

namespace TIMGE
{
	class Exception
	{
		public:
			Exception();
			Exception(std::string message, const std::source_location location = std::source_location::current());

			[[nodiscard]] virtual const std::string& What() const;

			[[nodiscard]] virtual const std::string& operator()() const;
		private:
			std::string mWhat;
	};
}

#endif // EXCEPTION_HPP

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

namespace TIMGE
{
	class Exception
	{
		public:
			Exception(const std::string& message);

			[[nodiscard]] virtual const std::string& What() const;

			[[nodiscard]] virtual const std::string& operator()() const;
		private:
			std::string mWhat;
	};
}

#endif // EXCEPTION_HPP

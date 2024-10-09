#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "TIMGE/Window.hpp"
#include <cstdint>
#include <string_view>

namespace TIMGE
{
    class ApplicationBase
    {
	public:
	ApplicationBase();
	virtual ~ApplicationBase() = 0;
	virtual void Run() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
    };

    class Application : public ApplicationBase
    {
	public:

	Application(const Window::Info& info);
	Application(std::string_view title, uint32_t width, uint32_t height);
	virtual ~Application() = 0;
	virtual void Run() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	Window& GetWindow();

	public:
	
	Window mWindow;
    };
}

#endif //APPLICATION_HPP

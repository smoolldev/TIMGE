#include "TIMGE/Application.hpp"

namespace TIMGE
{
    ApplicationBase::ApplicationBase()
    {
        if (!glfwInit()) {
	   throw "Failed to initialize GLFW!\n";
        }
    }

    ApplicationBase::~ApplicationBase() {
        glfwTerminate();
    }

    Application::Application(const Window::Info& info)
     : ApplicationBase(), mWindow(info)
    {}

    Application::Application(std::string_view title, uint32_t width, uint32_t height)
     : Application(
	{
    	    title,
    	    width,
    	    height,
    	    0, 0, 0, 0,
    	    4, 6,
    	    Window::RESIZABLE | Window::VISIBLE | Window::DECORATED |
    	    Window::FOCUSED | Window::AUTO_ICONIFY | Window::CENTER_CURSOR |
    	    Window::FOCUS_ON_SHOW,
    	    "Default"
    	}
    )
    {}

    Application::~Application()
    {}

    Window& Application::GetWindow(){
	return mWindow;
    }
}

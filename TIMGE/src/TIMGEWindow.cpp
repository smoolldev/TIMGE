#include "TIMGE/TIMGEWindow.hpp"

#include <GLFW/glfw3.h>

namespace TIMGE
{
    Window::Window(std::string_view title, uint32_t width, uint32_t height)
    {
	mWindow = glfwCreateWindow()
    }
}

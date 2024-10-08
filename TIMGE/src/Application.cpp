#include <cstdint>
#include <string_view>

#include "TIMGE/Application.hpp"
#include "TIMGE/Window.hpp"

#include <GLFW/glfw3.h>

namespace TIMGE
{
    Application::Application(const Window::Info& info)
        : ApplicationBase(),
          mWindow(info)
    { }

    Application::Application(std::string_view title, uint32_t width, uint32_t height)
        : Application({ title,
                        width,
                        height,
                        0,
                        0,
                        0,
                        0,
                        4,
                        6,
                        Window::RESIZABLE | Window::VISIBLE | Window::DECORATED | Window::FOCUSED | Window::AUTO_ICONIFY | Window::CENTER_CURSOR | Window::FOCUS_ON_SHOW
          })
    { }

    Application::~Application()
    { }
}

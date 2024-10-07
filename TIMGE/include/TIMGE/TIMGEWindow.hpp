#ifdef TIMGE_WINDOW_HPP
#define TIMGE_WINDOW_HPP

#include <string_view>

namespace TIMGE
{
    class Window
    {
        Window(std::string_view title, uint32_t width, uint32_t height);
        ~Window();
    };
}

#endif // TIMGE_WINDOW_HPP

#ifndef TIMGE_WINDOW_HPP
#define TIMGE_WINDOW_HPP

#include <string_view>
#include <cstdint>
#include <filesystem>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace TIMGE
{
    class Window
    {
        public:
            using FLAGS = uint32_t;

            struct Info
            {
                std::string_view title;
                uint32_t width;
                uint32_t height;
                uint32_t minWidth;
                uint32_t minHeight;
                uint32_t maxWidth;
                uint32_t maxHeight;
                uint32_t openGLVersionMajor;
                uint32_t openGLVersionMinor;
                FLAGS flags;
                std::filesystem::path iconPath;
            };

            static constexpr FLAGS RESIZABLE = (1 << 0);
            static constexpr FLAGS VISIBLE = (1 << 1);
            static constexpr FLAGS DECORATED = (1 << 2);
            static constexpr FLAGS FOCUSED = (1 << 3);
            static constexpr FLAGS AUTO_ICONIFY = (1 << 4);
            static constexpr FLAGS FLOATING = (1 << 5);
            static constexpr FLAGS MAXIMIZED = (1 << 6);
            static constexpr FLAGS CENTER_CURSOR = (1 << 7);
            static constexpr FLAGS TRANSPARENT_FRAMEBUFFER = (1 << 8);
            static constexpr FLAGS FOCUS_ON_SHOW = (1 << 9);
            static constexpr FLAGS SCALE_TO_MONITOR = (1 << 10);
            static constexpr FLAGS SCALE_FRAMEBUFFER = (1 << 11);

            Window(const Info& info);
            Window(std::string_view title, uint32_t width, uint32_t height);
            ~Window();

            friend class Application;
        public:
            static constexpr FLAGS mWINDOWHINTS[] = {
                GLFW_RESIZABLE,
                GLFW_VISIBLE,
                GLFW_DECORATED,
                GLFW_FOCUSED,
                GLFW_AUTO_ICONIFY,
                GLFW_FLOATING,
                GLFW_MAXIMIZED,
                GLFW_CENTER_CURSOR,
                GLFW_TRANSPARENT_FRAMEBUFFER,
                GLFW_FOCUS_ON_SHOW,
                GLFW_SCALE_TO_MONITOR,
                GLFW_SCALE_FRAMEBUFFER,
            };

            Info mInfo;

            GLFWwindow* mWindow;
    };
}

#endif // TIMGE_WINDOW_HPP

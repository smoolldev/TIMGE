#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Utils/Vector.hpp"
#include "Monitor.hpp"

#include <cstdint>
#include <filesystem>
#include <string_view>

namespace TIMGE
{
    class Window
    {
        public:
            using FLAGS = uint32_t;

            struct Info
            {
                std::string_view mTitle;
                uint32_t mWidth;
                uint32_t mHeight;
                uint32_t mMinWidth;
                uint32_t mMinHeight;
                uint32_t mMaxWidth;
                uint32_t mMaxHeight;
                uint32_t mOpenGLVersionMajor;
                uint32_t mOpenGLVersionMinor;
                FLAGS mFlags;
                std::filesystem::path mIconPath;
                bool mIsFullscreen;
            };

            Window(Info& info, Monitor& monitor);
            ~Window();

            GLFWwindow* GetWindow(); //TODO: Move to private and befriend with Application
            const Vector<int, 2>& GetPosition() const;
            const Vector<int, 2>& GetSize() const;
            const Vector<int, 2>& GetFramebufferSize() const;
            const Vector<int, 4>& GetFrameSize() const;
            const Vector<float, 2>& GetContentScale() const;
            float GetOpacity() const;
            GLFWmonitor* GetMonitor() const;

            void SetTitle(std::string_view title);
            void SetIcon(std::filesystem::path iconPath = "Default");
            void SetPosition(int x, int y);
            void SetAspectRatio(int numerator, int denominator);
            void SetSize(int width, int height);
            void SetOpacity(float opacity);
            void SetMonitor(GLFWmonitor* monitor, int x, int y, int width, int height, int refreshRate);
            void SetShouldClose(bool shouldClose);

            void Minimize();
            void Restore();
            void Maximize();
            void Show();
            void Hide();
            void Focus();
            void RequestAttention();
            void BorderlessFullscreen();
            void Fullscreen();

            bool ShouldClose();

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
        private:
            static constexpr uint32_t mWINDOWHINTS[]
            {
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
            };

            Info& mInfo;
            Monitor& mMonitor;
            GLFWwindow* mWindow;

            Vector<int, 2> mSize;
            Vector<int, 2> mPosition;
            Vector<int, 2> mFramebufferSize;
            Vector<int, 4> mFrameSize;
            Vector<float, 2> mContentScale;

            bool mIsFullscreen;

            static Window* mInstance;

            friend class Application;
    };
}
#endif // WINDOW_HPP

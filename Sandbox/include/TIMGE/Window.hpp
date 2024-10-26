#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Exception.hpp"
#include "Utils/Vector.hpp"
#include "Monitor.hpp"

#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>

namespace TIMGE
{
    class WindowException : public Exception
    {
        public:
            WindowException(std::string message);
    };

    class Window
    {
        public:
            using FLAGS = uint32_t;

            struct Info
            {
                std::string_view mTitle;
                V2ui32 mSize;
                V4ui32 mSizeLimits;
                V2i32 mPosition;
                V2ui32 mAspectRatio;
                float mOpacity;
                V2ui32 mOpenGLVersion;
                FLAGS mFlags;
            };

            Window(Info& info, Monitor& monitor);
            ~Window();

            [[nodiscard]] const std::string_view& GetTitle() const;
            [[nodiscard]] const V2i32& GetPosition() const;
            [[nodiscard]] const V2i32& GetSize() const;
            [[nodiscard]] const V4ui32& GetSizeLimits() const;
            [[nodiscard]] const V2i32& GetFramebufferSize() const;
            [[nodiscard]] const V2i32& GetAspectRatio() const;
            [[nodiscard]] const V4i32& GetFrameSize() const;
            [[nodiscard]] const V2f& GetContentScale() const;
            [[nodiscard]] float GetOpacity() const;
            [[nodiscard]] bool GetFullscreen() const;

            void SetTitle(std::string_view title);
            void SetIcon(std::filesystem::path iconPath);
            void SetPosition(V2i32 position);
            void SetAspectRatio(V2i32 aspectRatio);
            void SetSize(V2i32 size);
            void SetSizeLimits(V4ui32 sizeLimits);
            void SetOpacity(float opacity);
            void SetShouldClose(bool shouldClose);

            void ResetIcon();

            void Minimize();
            void Restore();
            void Maximize();
            void Show();
            void Hide();
            void Focus();
            void RequestAttention();
            void BorderlessFullscreen();
            void Fullscreen();

            [[nodiscard]] bool ShouldClose();

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
            static constexpr FLAGS BORDERLESS_FULLSCREEN = (1 << 11);
            static constexpr FLAGS FULLSCREEN = (1 << 12);
            static constexpr FLAGS VSYNC = (1 << 13);
        private:
        // WARNING: REMOVE WHEN IMGUI CONDITIONAL COMPILATION IS IMPLEMENTED!!!!!!!!!!!!!!!!!!!
        public:
            GLFWwindow* mGetWindow();
        private:
            void mUpdateMonitor();

            void mValidateInfo();

            void mCreateWindow();

            void mLoadGL();

            void mRetrieveSize();
            void mRetrievePosition();
            void mRetrieveFramebufferSize();
            void mRetrieveFrameSize();
            void mRetrieveContentScale();
            void mRetrieveMonitor();
            void mRetrieveVideoMode();

            void mInitializeAspectRatio();
            void mInitializeSizeBeforeFullscreen();
            void mInitializePositionBeforeFullscreen();

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

            V2i32 mFramebufferSize;
            V4i32 mFrameSize;
            V2f mContentScale;

            V2i32 mSizeBeforeFullscreen;
            V2i32 mPositionBeforeFullscreen;
            GLFWmonitor* mFullscreenMonitor;
            const GLFWvidmode* mVidMode;

            static Window* mInstance;

            friend class Application;
            friend class Mouse;
            friend class Keyboard;
    };
}
#endif // WINDOW_HPP

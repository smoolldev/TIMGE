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

    static constexpr uint32_t ASPECT_RATIO_DONT_CARE = std::numeric_limits<decltype(ASPECT_RATIO_DONT_CARE)>::max();
    static constexpr uint32_t SIZE_LIMITS_DONT_CARE = std::numeric_limits<decltype(SIZE_LIMITS_DONT_CARE)>::max();
    static constexpr int32_t POSITION_DONT_CARE = std::numeric_limits<decltype(POSITION_DONT_CARE)>::max();

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
            [[nodiscard]] const V2ui32& GetSize() const;
            [[nodiscard]] const V4ui32& GetSizeLimits() const;
            [[nodiscard]] const V2ui32& GetFramebufferSize() const;
            [[nodiscard]] const V2ui32& GetAspectRatio() const;
            [[nodiscard]] const V4ui32& GetFrameSize() const;
            [[nodiscard]] const V2f& GetContentScale() const;
            [[nodiscard]] float GetOpacity() const;
            [[nodiscard]] bool GetState(FLAGS flags) const;
            [[nodiscard]] bool GetBorderlessFullscreen() const;
            [[nodiscard]] bool GetFullscreen() const;
            [[nodiscard]] bool ShouldClose();

            void SetTitle(const std::string_view& title);
            void SetIcon(const std::filesystem::path& iconPath);
            void SetPosition(const V2i32& position);
            void SetAspectRatio(const V2ui32& aspectRatio);
            void SetSize(const V2ui32& size);
            void SetSizeLimits(const V4ui32& sizeLimits);
            void SetOpacity(float opacity);
            void SetShouldClose(bool shouldClose);

            void ToggleResizable();
            void ToggleDecorated();
            void ToggleAutoIconify();
            void ToggleFloating();
            void ToggleCenterCursor();
            void ToggleTransparentFramebuffer();
            void ToggleFocusOnShow();
            void ToggleScaleToMonitor();
            void ToggleVSync();

            void ResetIcon();
            void ResetState(FLAGS flags);

            void Minimize();
            void Restore();
            void Maximize();
            void Show();
            void Hide();
            void Focus();
            void RequestAttention();
            void BorderlessFullscreen();
            void Fullscreen();

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
            static constexpr FLAGS MINIMIZED = (1 << 14);
        private:
        // WARNING: REMOVE WHEN IMGUI CONDITIONAL COMPILATION IS IMPLEMENTED!!!!!!!!!!!!!!!!!!!
        public:
            GLFWwindow* mGetWindow();
        private:
            void mUpdateMonitor();

            void mValidateInfo();
            void mValidateSize(const V2ui32& size);
            void mValidateSizeLimits(const V4ui32& sizeLimits);
            void mValidateAspectRatio(const V2ui32& aspectRatio);
            void mValidateOpacity(float opacity);
            void mValidateOpenGLVersion(const V2ui32& version);
            void mValidateFlags(FLAGS flags);

            void mValidateFullscreen_BorderlessFullscreen(FLAGS flags);
            void mValidateVisible_Fullscreen(FLAGS flags);
            void mValidateDecorated_Fullscreen(FLAGS flags);
            void mValidateDecorated_BorderlessFullscreen(FLAGS flags);
            void mValidateFocused_Minimized(FLAGS flags);
            void mValidateFocused_CenterCursor(FLAGS flags);
            void mValidateCenterCursor_Minimized(FLAGS flags);
            void mValidateMinimized_Maximized(FLAGS flags);
 
            [[nodiscard]] bool mInvalidSizeMinBound(const V2ui32& size) const;
            [[nodiscard]] bool mInvalidSizeMaxBound(const V2ui32& size) const;
            [[nodiscard]] bool mInvalidSizeLimits(const V4ui32& sizeLimits) const;
            [[nodiscard]] bool mInvalidAspectRatio(const V2ui32& aspectRatio) const;
            [[nodiscard]] bool mInvalidOpacity(float opacity) const;
            [[nodiscard]] bool mInvalidOpenGLVersion(const V2ui32& version) const;

            [[nodiscard]] bool mConflictFullscreen_BorderlessFullscreen(FLAGS flags) const;
            [[nodiscard]] bool mConflictVisible_Fullscreen(FLAGS flags) const;
            [[nodiscard]] bool mConflictDecorated_Fullscreen(FLAGS flags) const;
            [[nodiscard]] bool mConflictDecorated_BorderlessFullscreen(FLAGS flags) const;
            [[nodiscard]] bool mConflictFocused_Minimized(FLAGS flags) const;
            [[nodiscard]] bool mConflictFocused_CenterCursor(FLAGS flags) const;
            [[nodiscard]] bool mConflictCenterCursor_Minimized(FLAGS flags) const;
            [[nodiscard]] bool mConflictMinimized_Maximized(FLAGS flags) const;

            void mCreateWindow();

            void mLoadGL();

            void mRetrieveFramebufferSize();
            void mRetrieveFrameSize();
            void mRetrieveContentScale();
            void mRetrieveMonitor();
            void mRetrieveVideoMode();

            void mInitializeSizeBeforeFullscreen();
            void mInitializePositionBeforeFullscreen();

            void mToggleOnBorderlessFullscreen();
            void mToggleOffBorderlessFullscreen();
            void mToggleOnFullscreen();
            void mToggleOffFullscreen();

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

            V2ui32 mFramebufferSize;
            V4ui32 mFrameSize;
            V2f mContentScale;

            V2ui32 mSizeBeforeFullscreen;
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

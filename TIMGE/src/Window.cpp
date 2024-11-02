#include "TIMGE/Window.hpp"
#include "TIMGE/Exception.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <string>
#include <array>
#include <filesystem>
#include <format>

#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

namespace TIMGE
{
    WindowException::WindowException(std::string message)
     : Exception(std::format("Window: {}", message))
    {}

    Window *Window::mInstance = nullptr;

    Window::Window(Window::Info &info, Monitor& monitor) 
     :  mInfo{info}, 
        mMonitor{monitor}, 
        mWindow{nullptr}
    {
        if (mInstance) {
            throw WindowException("Only one instance of Window is allowed!");
        }

        mInstance = this;

        mRetrieveMonitor();
        mRetrieveVideoMode();

        mValidateInfo();
        mValidateFlags(mInfo.mFlags);

        mInitializeSizeBeforeFullscreen();
        mInitializePositionBeforeFullscreen();

        mCreateWindow();

        mLoadGL();

        mRetrieveFramebufferSize();
        mRetrieveFrameSize();
        mRetrieveContentScale();

        SetSizeLimits(mInfo.mSizeLimits);
        SetAspectRatio(mInfo.mAspectRatio);
        SetOpacity(mInfo.mOpacity);
    }

    Window::~Window() {
        glfwDestroyWindow(mWindow);
    }

    [[nodiscard]] const std::string_view& Window::GetTitle() const {
        return mInfo.mTitle;
    }

    [[nodiscard]] const V2i32& Window::GetPosition() const {
        return mInfo.mPosition;
    }

    [[nodiscard]] const V2ui32& Window::GetSize() const {
        return mInfo.mSize;
    }

    [[nodiscard]] const V4ui32& Window::GetSizeLimits() const {
        return mInfo.mSizeLimits;
    }

    [[nodiscard]] const V2ui32& Window::GetFramebufferSize() const {
        return mFramebufferSize;
    }

    [[nodiscard]] const V2ui32& Window::GetAspectRatio() const {
        return mInfo.mAspectRatio;
    }

    [[nodiscard]] const V4ui32& Window::GetFrameSize() const {
        return mFrameSize;
    }

    [[nodiscard]] const V2f& Window::GetContentScale() const {
        return mContentScale;
    }

    [[nodiscard]] float Window::GetOpacity() const {
        return mInfo.mOpacity;
    }

    [[nodiscard]] bool Window::GetState(FLAGS flags) const {
        return mInfo.mFlags & flags;
    }

    void Window::SetTitle(const std::string_view& title) {
        glfwSetWindowTitle(mWindow, title.data());
        mInfo.mTitle = title;
    }

    void Window::SetIcon(const std::filesystem::path& iconPath)
    {
        if (std::filesystem::exists(iconPath))
        {
            GLFWimage image;

            image.pixels = stbi_load(iconPath.string().c_str(), &image.width, &image.height, nullptr, 4);

            glfwSetWindowIcon(mWindow, 1, &image);

            stbi_image_free(image.pixels);
        } else {
            throw WindowException(std::format("Icon at path: \"{}\" does not exist.", iconPath.string()));
        }
    }

    void Window::SetPosition(const V2i32& position) {
        glfwSetWindowPos(mWindow, position[V2i32::X], position[V2i32::Y]);
    }

    void Window::SetAspectRatio(const V2ui32& aspectRatio) {
        mValidateAspectRatio(aspectRatio);

        glfwSetWindowAspectRatio(
            mWindow, 
            aspectRatio[V2ui32::NUMERATOR] == ASPECT_RATIO_DONT_CARE ?
                GLFW_DONT_CARE : aspectRatio[V2i32::NUMERATOR], 
            aspectRatio[V2ui32::DENOMINATOR] == ASPECT_RATIO_DONT_CARE ?
                GLFW_DONT_CARE : aspectRatio[V2i32::DENOMINATOR]
        );

        mInfo.mAspectRatio = aspectRatio;
    }

    void Window::SetSize(const V2ui32& size)
    {
        mValidateSize(size);
        glfwSetWindowSize(mWindow, size[V2i32::WIDTH], size[V2i32::HEIGHT]);
    }

    void Window::SetSizeLimits(const V4ui32& sizeLimits)
    {
        mValidateSizeLimits(sizeLimits);

        glfwSetWindowSizeLimits(
            mWindow,
            static_cast<int>((sizeLimits[V4ui32::MIN_WIDTH] == SIZE_LIMITS_DONT_CARE) ?
                GLFW_DONT_CARE : sizeLimits[V4ui32::MIN_WIDTH]),
            static_cast<int>((sizeLimits[V4ui32::MIN_HEIGHT] == SIZE_LIMITS_DONT_CARE) ?
                GLFW_DONT_CARE : sizeLimits[V4ui32::MIN_HEIGHT]),
            static_cast<int>((sizeLimits[V4ui32::MAX_WIDTH] == SIZE_LIMITS_DONT_CARE) ?
                GLFW_DONT_CARE : sizeLimits[V4ui32::MAX_WIDTH]),
            static_cast<int>((sizeLimits[V4ui32::MAX_HEIGHT] == SIZE_LIMITS_DONT_CARE) ?
                GLFW_DONT_CARE : sizeLimits[V4ui32::MAX_HEIGHT])
        );

        mInfo.mSizeLimits = sizeLimits;
    }

    void Window::SetOpacity(float opacity) {
        mValidateOpacity(opacity);
        glfwSetWindowOpacity(mWindow, opacity);
        mInfo.mOpacity = opacity;
    }

    void Window::SetShouldClose(bool shouldClose) {
        glfwSetWindowShouldClose(mWindow, shouldClose);
    }

    void Window::ToggleResizable() {
        mInfo.mFlags ^= RESIZABLE;

        glfwSetWindowAttrib(mWindow, GLFW_RESIZABLE, GetState(RESIZABLE));
    }

    void Window::ToggleDecorated() {
        mInfo.mFlags ^= DECORATED;

        glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GetState(DECORATED));
    }

    void Window::ToggleAutoIconify() {
        mInfo.mFlags ^= AUTO_ICONIFY;

        glfwSetWindowAttrib(mWindow, GLFW_AUTO_ICONIFY, GetState(AUTO_ICONIFY));
    }

    void Window::ToggleFloating() {
        mInfo.mFlags ^= FLOATING;

        glfwSetWindowAttrib(mWindow, GLFW_FLOATING, GetState(FLOATING));
    }

    void Window::ToggleCenterCursor() {
        mInfo.mFlags ^= CENTER_CURSOR;

        glfwSetWindowAttrib(mWindow, GLFW_CENTER_CURSOR, GetState(CENTER_CURSOR));
    }

    void Window::ToggleTransparentFramebuffer() {
        mInfo.mFlags ^= TRANSPARENT_FRAMEBUFFER;

        glfwSetWindowAttrib(mWindow, GLFW_TRANSPARENT_FRAMEBUFFER, GetState(TRANSPARENT_FRAMEBUFFER));
    }

    void Window::ToggleFocusOnShow() {
        mInfo.mFlags ^= FOCUS_ON_SHOW;

        glfwSetWindowAttrib(mWindow, GLFW_FOCUS_ON_SHOW, GetState(FOCUS_ON_SHOW));
    }

    void Window::ToggleScaleToMonitor() {
        mInfo.mFlags ^= SCALE_TO_MONITOR;

        glfwSetWindowAttrib(mWindow, GLFW_SCALE_TO_MONITOR, GetState(SCALE_TO_MONITOR));
    }

    void Window::ToggleVSync() {
        mInfo.mFlags ^= VSYNC;

        glfwSwapInterval(GetState(VSYNC));
    }

    void Window::ResetIcon() {
        glfwSetWindowIcon(mWindow, 0, nullptr);
    }

    void Window::Minimize() {
        glfwIconifyWindow(mWindow);
    }

    void Window::Restore() {
        if (GetState(FULLSCREEN)) {
            Fullscreen();
        } else if (GetState(BORDERLESS_FULLSCREEN)) {
            BorderlessFullscreen();
        } else {
            glfwRestoreWindow(mWindow);
        }
    }

    void Window::Maximize() {
        if (GetState(FULLSCREEN)) {
            mToggleOffFullscreen();
        } else if (GetState(BORDERLESS_FULLSCREEN)) {
            mToggleOffBorderlessFullscreen();
        }
        glfwMaximizeWindow(mWindow);
    }

    void Window::Show() {
        glfwShowWindow(mWindow);

        mInfo.mFlags |= VISIBLE;
    }

    void Window::Hide() {
        if (GetState(FULLSCREEN)) {
            throw WindowException("Fullscreen windows cannot be hidden.");
        }

        glfwHideWindow(mWindow);

        mInfo.mFlags &= ~VISIBLE; 
    }

    void Window::Focus() {
        glfwFocusWindow(mWindow);
    }

    void Window::RequestAttention() {
        glfwRequestWindowAttention(mWindow);
    }

    void Window::BorderlessFullscreen()
    {
        if (!GetState(BORDERLESS_FULLSCREEN)) {
            mToggleOnBorderlessFullscreen();
        } else {
            mToggleOffBorderlessFullscreen();
        }

        mInfo.mFlags ^= BORDERLESS_FULLSCREEN;
    }

    void Window::Fullscreen()
    {
        if (!GetState(FULLSCREEN)) {
            mToggleOnFullscreen();
        } else {
            mToggleOffFullscreen();
        }

        mInfo.mFlags ^= FULLSCREEN;
    }

    [[nodiscard]] bool Window::ShouldClose() {
        return glfwWindowShouldClose(mWindow);
    }

    GLFWwindow *Window::mGetWindow() {
        return mWindow;
    }

    void Window::mUpdateMonitor()
    {
        mValidateFullscreen_BorderlessFullscreen(mInfo.mFlags);
 
        mFullscreenMonitor = mMonitor.mGetMonitor();
        mVidMode = glfwGetVideoMode(mFullscreenMonitor);

        V2i32 new_position = mMonitor.GetWorkareaPosition();
        V2ui32 workarea_size = mMonitor.GetWorkareaSize();

        new_position[V2i32::X] += (workarea_size[V2ui32::WIDTH] - mInfo.mSize[V2ui32::WIDTH]) / 2;
        new_position[V2i32::Y] += (workarea_size[V2ui32::HEIGHT] - mInfo.mSize[V2ui32::HEIGHT]) / 2;

        mValidateSize(mInfo.mSize);

        if (!GetState(FULLSCREEN) && !GetState(BORDERLESS_FULLSCREEN)) {
            glfwSetWindowMonitor(
                mWindow, nullptr, new_position[V2i32::X], new_position[V2i32::Y],
                mInfo.mSize[V2ui32::WIDTH], mInfo.mSize[V2ui32::HEIGHT],
                0
            );
        }
        else if (GetState(FULLSCREEN)) {
            mToggleOnFullscreen();
        } else if (GetState(BORDERLESS_FULLSCREEN)) {
            mToggleOnBorderlessFullscreen();
        }
    }

    void Window::mValidateInfo()
    {
        mValidateSize(mInfo.mSize);
        mValidateSizeLimits(mInfo.mSizeLimits);
        mValidateAspectRatio(mInfo.mAspectRatio);
        mValidateOpacity(mInfo.mOpacity);
        mValidateOpenGLVersion(mInfo.mOpenGLVersion);
        mValidateFullscreen_BorderlessFullscreen(mInfo.mFlags); 
        mValidateFlags(mInfo.mFlags);
    }

    void Window::mCreateWindow()
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mInfo.mOpenGLVersion[V2ui32::GL_MAJOR]);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mInfo.mOpenGLVersion[V2ui32::GL_MINOR]);

        for (int i = 0; i < sizeof(mWINDOWHINTS) / sizeof(mWINDOWHINTS[0]); i++) {
            glfwWindowHint(mWINDOWHINTS[i], (mInfo.mFlags >> i) & 1);
        }

        mWindow = glfwCreateWindow(
            static_cast<int>(mInfo.mSize[V2ui32::WIDTH]), 
            static_cast<int>(mInfo.mSize[V2ui32::HEIGHT]),
            mInfo.mTitle.data(), nullptr, nullptr
        );

        if (!mWindow) {
            throw WindowException("Failed to create window!");
        }

        if (GetState(FULLSCREEN)) {
            mToggleOnFullscreen();
        } else if (GetState(BORDERLESS_FULLSCREEN)) {
            mToggleOnBorderlessFullscreen();
        }
    }

    void Window::mLoadGL()
    {
        glfwMakeContextCurrent(mWindow);
        if (!gladLoadGL()) {
            throw WindowException("Failed to load OpenGL!");
        }

        glfwSwapInterval(GetState(VSYNC));
    }

    void Window::mRetrieveFramebufferSize() {
        glfwGetFramebufferSize(
            mWindow, 
            reinterpret_cast<int*>(&mFramebufferSize[V2ui32::WIDTH]), 
            reinterpret_cast<int*>(&mFramebufferSize[V2ui32::HEIGHT])
        );
    }

    void Window::mRetrieveFrameSize()
    {
        glfwGetWindowFrameSize(
            mWindow, 
            reinterpret_cast<int*>(&mFrameSize[V2i32::X]),
            reinterpret_cast<int*>(&mFrameSize[V2i32::Y]),
            reinterpret_cast<int*>(&mFrameSize[V2i32::Z]),
            reinterpret_cast<int*>(&mFrameSize[V2i32::W])
        );
    }

    void Window::mRetrieveContentScale() {
        glfwGetWindowContentScale(
            mWindow, 
            &mContentScale[V2f::X], 
            &mContentScale[V2f::Y]
        );
    }

    void Window::mRetrieveMonitor() {
        mFullscreenMonitor = mMonitor.mGetMonitor();
    }

    void Window::mRetrieveVideoMode() {
        mVidMode = glfwGetVideoMode(mFullscreenMonitor);
    }

    void Window::mInitializeSizeBeforeFullscreen() {
        mSizeBeforeFullscreen = mInfo.mSize;
    }

    void Window::mInitializePositionBeforeFullscreen() {
        mPositionBeforeFullscreen = mInfo.mPosition;
    }

    void Window::mToggleOnBorderlessFullscreen()
    {
        mInfo.mFlags &= ~DECORATED;
        mSizeBeforeFullscreen = mInfo.mSize;
        mPositionBeforeFullscreen = mInfo.mPosition;

        glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_FALSE);
        SetSize(V2ui32{ 
            static_cast<uint32_t>(mVidMode->width),
            static_cast<uint32_t>(mVidMode->height)
        });
        SetPosition({ 0, 0 });
    }

    void Window::mToggleOffBorderlessFullscreen()
    {
        mInfo.mFlags |= DECORATED;

        glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_TRUE);
        SetSize(mSizeBeforeFullscreen);
        SetPosition(mPositionBeforeFullscreen);
    }

    void Window::mToggleOnFullscreen() {
        mSizeBeforeFullscreen = mInfo.mSize;
        mPositionBeforeFullscreen = mInfo.mPosition;

        glfwSetWindowMonitor(mWindow, mFullscreenMonitor, 0, 0, mVidMode->width, mVidMode->height, mVidMode->refreshRate);
    }

    void Window::mToggleOffFullscreen()
    {
        glfwSetWindowMonitor(
            mWindow, nullptr,
            mPositionBeforeFullscreen[V2i32::X], mPositionBeforeFullscreen[V2i32::Y],
            mSizeBeforeFullscreen[V2i32::WIDTH], mSizeBeforeFullscreen[V2i32::HEIGHT],
            0
        );
        SetSize(mSizeBeforeFullscreen);
        SetPosition(mPositionBeforeFullscreen);
    }

    [[nodiscard]] bool Window::mInvalidSizeMinBound(const V2ui32& size) const
    {
        return size[V2ui32::WIDTH] == 0 || size[V2ui32::HEIGHT] == 0;
    }

    [[nodiscard]] bool Window::mInvalidSizeMaxBound(const V2ui32& size) const {
        return size[V2ui32::WIDTH] > static_cast<uint32_t>(mVidMode->width)
            || size[V2ui32::HEIGHT] > static_cast<uint32_t>(mVidMode->height);
    }

    [[nodiscard]] bool Window::mInvalidSizeLimits(const V4ui32& sizeLimits) const {
        return sizeLimits[V2ui32::MAX_WIDTH] != SIZE_LIMITS_DONT_CARE 
            && sizeLimits[V2ui32::MAX_WIDTH] > static_cast<uint32_t>(mVidMode->width)
            || sizeLimits[V2ui32::MAX_HEIGHT] != SIZE_LIMITS_DONT_CARE
            && sizeLimits[V2ui32::MAX_HEIGHT] > static_cast<uint32_t>(mVidMode->height);
    }

    [[nodiscard]] bool Window::mInvalidAspectRatio(const V2ui32& aspectRatio) const {
        return aspectRatio[V2ui32::NUMERATOR] != ASPECT_RATIO_DONT_CARE
            && aspectRatio[V2ui32::NUMERATOR] > mInfo.mSize[V2ui32::WIDTH]
            || aspectRatio[V2ui32::DENOMINATOR] != ASPECT_RATIO_DONT_CARE 
            && aspectRatio[V2ui32::DENOMINATOR] > mInfo.mSize[V2ui32::HEIGHT];
    }

    [[nodiscard]] bool Window::mInvalidOpacity(float opacity) const {
        return  opacity < 0.0f || opacity > 1.0f;
    }

    [[nodiscard]] bool Window::mInvalidOpenGLVersion(const V2ui32& version) const 
    {
        static std::array <V2ui32, 12> GLVers
        {
            V2ui32{2, 1}, V2ui32{3, 0}, V2ui32{3, 1},
            V2ui32{3, 2}, V2ui32{3, 3}, V2ui32{4, 0},
            V2ui32{4, 1}, V2ui32{4, 2}, V2ui32{4, 3},
            V2ui32{4, 4}, V2ui32{4, 5}, V2ui32{4, 6},
        };

        for (const auto& ver: GLVers) {
            if (ver == version) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool Window::mConflictFullscreen_BorderlessFullscreen(FLAGS flags) const {
        return GetState(FULLSCREEN) && GetState(BORDERLESS_FULLSCREEN);
    }

    [[nodiscard]] bool Window::mConflictVisible_Fullscreen(FLAGS flags) const {
        return !GetState(VISIBLE) && GetState(FULLSCREEN);
    }

    [[nodiscard]] bool Window::mConflictDecorated_Fullscreen(FLAGS flags) const {
        return GetState(DECORATED) && GetState(FULLSCREEN);
    }

    [[nodiscard]] bool Window::mConflictDecorated_BorderlessFullscreen(FLAGS flags) const {
        return GetState(DECORATED) && GetState(BORDERLESS_FULLSCREEN);
    }

    [[nodiscard]] bool Window::mConflictFocused_Minimized(FLAGS flags) const {
        return GetState(FOCUSED) && GetState(MINIMIZED);
    }

    [[nodiscard]] bool Window::mConflictFocused_CenterCursor(FLAGS flags) const {
        return !GetState(FOCUSED) && GetState(CENTER_CURSOR);
    }

    [[nodiscard]] bool Window::mConflictCenterCursor_Minimized(FLAGS flags) const {
        return GetState(CENTER_CURSOR) && GetState(MINIMIZED);
    }

    [[nodiscard]] bool Window::mConflictMinimized_Maximized(FLAGS flags) const {
        return GetState(MINIMIZED) && GetState(MAXIMIZED);
    }

    void Window::mValidateSize(const V2ui32& size)
    {
        if (mInvalidSizeMinBound(mInfo.mSize)) {
            throw WindowException("Size cannot be 0.");
        } else if (mInvalidSizeMaxBound(mInfo.mSize)) {
            throw WindowException("Size cannot be bigger than monitor allows for.");
        }
    }

    void Window::mValidateSizeLimits(const V4ui32& sizeLimits)
    {
        if (mInvalidSizeLimits(mInfo.mSizeLimits)) {
            throw WindowException("Size limits cannot be bigger than monitor allows for.");
        }
    }

    void Window::mValidateAspectRatio(const V2ui32& aspectRatio)
    {
        if (mInvalidAspectRatio(mInfo.mAspectRatio)) {
            throw WindowException("Aspect ratio cannot be bigger than window size.");
        }
    }

    void Window::mValidateOpacity(float opacity)
    {
        if (mInvalidOpacity(mInfo.mOpacity)) {
            throw WindowException("Opacity must be in range [0;1].");
        }
    }

    void Window::mValidateOpenGLVersion(const V2ui32& version)
    {
        if (mInvalidOpenGLVersion(mInfo.mOpenGLVersion)) {
            throw WindowException("Invalid OpenGL version."); 
        }
    }

    void Window::mValidateFlags(FLAGS flags)
    {
        mValidateFullscreen_BorderlessFullscreen(flags);
        mValidateVisible_Fullscreen(flags);
        mValidateDecorated_Fullscreen(flags);
        mValidateDecorated_BorderlessFullscreen(flags);
        mValidateFocused_Minimized(flags);
        mValidateFocused_CenterCursor(flags);
        mValidateCenterCursor_Minimized(flags);
        mValidateMinimized_Maximized(flags);
    }

    void Window::mValidateFullscreen_BorderlessFullscreen(FLAGS flags)
    {
        if (mConflictFullscreen_BorderlessFullscreen(flags)) {
            throw WindowException("Window cannot be both Fullscreen and Borderless Fullscreen.");
        }
    }

    void Window::mValidateVisible_Fullscreen(FLAGS flags)
    {
        if (mConflictVisible_Fullscreen(flags)) {
            throw WindowException("Window cannot be both Hidden and Fullscreen.");
        }
    }

    void Window::mValidateDecorated_Fullscreen(FLAGS flags)
    {
        if (mConflictDecorated_Fullscreen(flags)) {
            throw WindowException("Window cannot be both Decorated and Fullscreen.");
        }
    }

    void Window::mValidateDecorated_BorderlessFullscreen(FLAGS flags)
    {
        if (mConflictDecorated_BorderlessFullscreen(flags)) {
            throw WindowException("Window cannot be both Decorated and Borderless Fullscreen.");
        }
    }

    void Window::mValidateFocused_Minimized(FLAGS flags)
    {
        if (mConflictFocused_Minimized(flags)) {
            throw WindowException("Window cannot be both Focused and Minimized.");
        }
    }

    void Window::mValidateFocused_CenterCursor(FLAGS flags)
    {
        if (mConflictFocused_CenterCursor(flags)) {
            throw WindowException("Cursor cannot be centered on unfocused window.");
        }
    }

    void Window::mValidateCenterCursor_Minimized(FLAGS flags)
    {
        if (mConflictCenterCursor_Minimized(flags)) {
            throw WindowException("Cursor cannot be centered on minimized window.");
        }
    }

    void Window::mValidateMinimized_Maximized(FLAGS flags)
    {
        if (mConflictMinimized_Maximized(flags)) {
            throw WindowException("Window cannot be both Minimized and Maximized.");
        }
    }
} // namespace TIMGE

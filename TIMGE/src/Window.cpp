#include "TIMGE/Window.hpp"
#include "TIMGE/Exception.hpp"
#include "TIMGE/Utils/Vector.hpp"

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

        mInitializeSizeBeforeFullscreen();
        mInitializePositionBeforeFullscreen();

        mCreateWindow();

        mLoadGL();

        mRetrieveFramebufferSize();
        mRetrieveFrameSize();
        mRetrieveContentScale();

        if (mInfo.mPosition == V2i32{POSITION_DONT_CARE, POSITION_DONT_CARE}) {
            SetPosition(mInfo.mPosition);
        }
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

    [[nodiscard]] bool Window::GetFlagsState(FLAGS flags) const {
        return mInfo.mFlags & flags;
    }

    [[nodiscard]] bool Window::GetBorderlessFullscreen() const {
        return mInfo.mFlags & BORDERLESS_FULLSCREEN;
    }
    [[nodiscard]] bool Window::GetFullscreen() const {
        return mInfo.mFlags & FULLSCREEN;
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
                mInfo.mSize[V2ui32::WIDTH] : aspectRatio[V2i32::NUMERATOR], 
            aspectRatio[V2ui32::DENOMINATOR] == ASPECT_RATIO_DONT_CARE ?
                mInfo.mSize[V2ui32::HEIGHT] : aspectRatio[V2i32::DENOMINATOR]
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

    void Window::ResetIcon() {
        glfwSetWindowIcon(mWindow, 0, nullptr);
    }

    void Window::Minimize() {
        glfwIconifyWindow(mWindow);
    }

    void Window::Restore() {
        glfwRestoreWindow(mWindow);
    }

    void Window::Maximize() {
        glfwMaximizeWindow(mWindow);
    }

    void Window::Show() {
        glfwShowWindow(mWindow);
    }

    void Window::Hide() {
        glfwHideWindow(mWindow);
    }

    void Window::Focus() {
        glfwFocusWindow(mWindow);
    }

    void Window::RequestAttention() {
        glfwRequestWindowAttention(mWindow);
    }

    void Window::BorderlessFullscreen()
    {
        if (!GetBorderlessFullscreen()) {
            mToggleOnBorderlessFullscreen();
        } else {
            mToggleOffBorderlessFullscreen();
        }

        mInfo.mFlags ^= BORDERLESS_FULLSCREEN;
    }

    void Window::Fullscreen()
    {
        if (!GetFullscreen()) {
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
        mValidateFullscreenFlags(mInfo.mFlags);
 
        mFullscreenMonitor = mMonitor.mGetMonitor();
        mVidMode = glfwGetVideoMode(mFullscreenMonitor);
        mValidateSize(mInfo.mSize);
        glfwSetWindowMonitor(
            mWindow, mFullscreenMonitor, 0, 0,
            mInfo.mSize[V2ui32::WIDTH], mInfo.mSize[V2ui32::HEIGHT],
            0
        );
        if (mInfo.mFlags & FULLSCREEN) {
            mToggleOnFullscreen();
        } else if (mInfo.mFlags & BORDERLESS_FULLSCREEN) {
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
        mValidateFullscreenFlags(mInfo.mFlags); 
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

        if (mInfo.mFlags & FULLSCREEN) {
            mToggleOnFullscreen();
        } else if (mInfo.mFlags & BORDERLESS_FULLSCREEN) {
            mToggleOnBorderlessFullscreen();
        }
    }

    void Window::mLoadGL()
    {
        glfwMakeContextCurrent(mWindow);
        if (!gladLoadGL()) {
            throw WindowException("Failed to load OpenGL!");
        }
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
        glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_TRUE);
        SetSize({ mSizeBeforeFullscreen[V2i32::WIDTH], mSizeBeforeFullscreen[V2i32::HEIGHT] });
        SetPosition({ mPositionBeforeFullscreen[V2i32::X], mPositionBeforeFullscreen[V2i32::Y] });
    }

    void Window::mToggleOnFullscreen() {
        mSizeBeforeFullscreen = mInfo.mSize;
        mPositionBeforeFullscreen = mInfo.mPosition;

        glfwSetWindowMonitor(mWindow, mFullscreenMonitor, 0, 0, mVidMode->width, mVidMode->height, mVidMode->refreshRate);
    }

    void Window::mToggleOffFullscreen()
    {
        glfwSetWindowMonitor(mWindow, nullptr, mPositionBeforeFullscreen[V2i32::X], mPositionBeforeFullscreen[V2i32::Y], mSizeBeforeFullscreen[V2i32::WIDTH], mSizeBeforeFullscreen[V2i32::HEIGHT], 0);
        SetSize({ mSizeBeforeFullscreen[V2i32::WIDTH], mSizeBeforeFullscreen[V2i32::HEIGHT] });
        SetPosition({ mPositionBeforeFullscreen[V2i32::X], mPositionBeforeFullscreen[V2i32::Y] });
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

        return std::find(GLVers.begin(), GLVers.end(), version) == GLVers.end();
    }

    [[nodiscard]] bool Window::mInvalidFullscreenFlags(FLAGS flags) const {
        return (flags & FULLSCREEN) && (flags & BORDERLESS_FULLSCREEN);
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

    void Window::mValidateFullscreenFlags(FLAGS flags)
    {
        if (mInvalidFullscreenFlags(mInfo.mFlags)) {
            throw WindowException("FULLSCREEN and BORDERLESS_FULLSCREEN flags cannot be set simultaneously.");
        }
    }

} // namespace TIMGE

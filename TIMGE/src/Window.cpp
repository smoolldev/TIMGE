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

        mValidateInfo();

        mCreateWindow();

        mLoadGL();

        mRetrieveSize();
        mRetrievePosition();
        mRetrieveFramebufferSize();
        mRetrieveFrameSize();
        mRetrieveContentScale();
        mRetrieveMonitor();
        mRetrieveVideoMode();

        mInitializeAspectRatio();
        mInitializeSizeBeforeFullscreen();
        mInitializePositionBeforeFullscreen();

        SetSizeLimits(mInfo.mSizeLimits);
    }

    Window::~Window() {
        glfwDestroyWindow(mWindow);
    }

    [[nodiscard]] const std::string_view& Window::GetTitle() const {
        return mInfo.mTitle;
    }

    [[nodiscard]] const V2i32& Window::GetPosition() const {
        return mPosition;
    }

    [[nodiscard]] const V2i32& Window::GetSize() const {
        return mSize;
    }

    [[nodiscard]] const V4ui32& Window::GetSizeLimits() const {
        return mSizeLimits;
    }

    [[nodiscard]] const V2i32& Window::GetFramebufferSize() const {
        return mFramebufferSize;
    }

    [[nodiscard]] const V2i32& Window::GetAspectRatio() const {
        return mAspectRatio;
    }

    [[nodiscard]] const V4i32& Window::GetFrameSize() const {
        return mFrameSize;
    }

    [[nodiscard]] const V2f& Window::GetContentScale() const {
        return mContentScale;
    }

    [[nodiscard]] float Window::GetOpacity() const {
        return glfwGetWindowOpacity(mWindow);
    }

    [[nodiscard]] bool Window::GetFullscreen() const {
        return mIsFullscreen;
    }

    void Window::SetTitle(std::string_view title) {
        mInfo.mTitle = title;
        glfwSetWindowTitle(mWindow, title.data());
    }

    void Window::SetIcon(std::filesystem::path iconPath)
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

    void Window::SetPosition(V2i32 position) {
        glfwSetWindowPos(mWindow, position[V2i32::X], position[V2i32::Y]);
    }

    void Window::SetAspectRatio(V2i32 aspectRatio) {
        glfwSetWindowAspectRatio(mWindow, aspectRatio[V2i32::NUMERATOR], aspectRatio[V2i32::DENOMINATOR]);
        mAspectRatio = aspectRatio;
    }

    void Window::SetSize(V2i32 size) {
        glfwSetWindowSize(mWindow, size[V2i32::WIDTH], size[V2i32::HEIGHT]);
    }

    void Window::SetSizeLimits(V4ui32 sizeLimits)
    {
        if ((sizeLimits[V4ui32::MAX_WIDTH] > mVidMode->width) || (sizeLimits[V4ui32::MAX_HEIGHT] > mVidMode->height)) {
            throw WindowException("Size limits bigger than monitor allows for.");
        }

        glfwSetWindowSizeLimits(
            mWindow,
            static_cast<int>((sizeLimits[V4ui32::MIN_WIDTH] == 0) ? GLFW_DONT_CARE : sizeLimits[V4ui32::MIN_WIDTH]),
            static_cast<int>((sizeLimits[V4ui32::MIN_HEIGHT] == 0) ? GLFW_DONT_CARE : sizeLimits[V4ui32::MIN_HEIGHT]),
            static_cast<int>((sizeLimits[V4ui32::MAX_WIDTH] == 0) ? GLFW_DONT_CARE : sizeLimits[V4ui32::MAX_WIDTH]),
            static_cast<int>((sizeLimits[V4ui32::MAX_HEIGHT] == 0) ? GLFW_DONT_CARE : sizeLimits[V4ui32::MAX_HEIGHT])
        );
    }

    void Window::SetOpacity(float opacity) {
        glfwSetWindowOpacity(mWindow, opacity);
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
        SetSize({ mSize[V2i32::WIDTH], mSize[V2i32::HEIGHT] });
        SetPosition({ mPosition[V2i32::X], mPosition[V2i32::Y] });

        glfwRestoreWindow(mWindow);
    }

    void Window::Maximize() {
        mSize = GetSize();
        mPosition = GetPosition();

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
        if (!mIsFullscreen)
        {
            mFullscreenMode = 2;
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_FALSE);
            SetSize({ mVidMode->width, mVidMode->height} );
            SetPosition({ 0, 0 });
        } else
        {
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_TRUE);
            SetSize({ mSizeBeforeFullscreen[V2i32::WIDTH], mSizeBeforeFullscreen[V2i32::HEIGHT] });
            SetPosition({ mPositionBeforeFullscreen[V2i32::X], mPositionBeforeFullscreen[V2i32::Y] });
            mFullscreenMode = 0;
        }

        mIsFullscreen = !mIsFullscreen;
    }

    void Window::Fullscreen()
    {
        if (!mIsFullscreen) {
            mFullscreenMode = 1;
            glfwSetWindowMonitor(mWindow, mFullscreenMonitor, 0, 0, mVidMode->width, mVidMode->height, mVidMode->refreshRate);
        } else {
            glfwSetWindowMonitor(mWindow, nullptr, mPositionBeforeFullscreen[V2i32::X], mPositionBeforeFullscreen[V2i32::Y], mSizeBeforeFullscreen[V2i32::WIDTH], mSizeBeforeFullscreen[V2i32::HEIGHT], 0);
            SetSize({ mSizeBeforeFullscreen[V2i32::WIDTH], mSizeBeforeFullscreen[V2i32::HEIGHT] });
            SetPosition({ mPositionBeforeFullscreen[V2i32::X], mPositionBeforeFullscreen[V2i32::Y] });
            mFullscreenMode = 0;
        }

        mIsFullscreen = !mIsFullscreen;
    }

    [[nodiscard]] bool Window::ShouldClose() {
        return glfwWindowShouldClose(mWindow);
    }

    GLFWwindow *Window::mGetWindow() {
        return mWindow;
    }

    void Window::mUpdateMonitor()
    {
        GLFWmonitor* monitor = mMonitor.mGetMonitor();
        const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
        if (mFullscreenMode == 0) {
           // TODO: Always set position after updating monitor 
        } else if (mFullscreenMode == 1) {
            
        } else if (mFullscreenMode == 2) {

        } else {
            throw WindowException("KURWA KUBA! MÓWIŁEM!");
        }
    }

    void Window::mValidateInfo()
    {
        // size
        if (mInfo.mSize == { 0, 0 }) {
            throw WindowException("Size cannot be 0.");
        } else if (mInfo.)
        // sizelimits
        // aspectratio
        // opacity
        // openglversion
        // fullscreen
    }

    void Window::mCreateWindow()
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mInfo.mOpenGLVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mInfo.mOpenGLVersionMinor);

        for (int i = 0; i < sizeof(mWINDOWHINTS) / sizeof(mWINDOWHINTS[0]); i++) {
            glfwWindowHint(mWINDOWHINTS[i], (mInfo.mFlags >> i) & 1);
        }

        mWindow = glfwCreateWindow(mInfo.mWidth, mInfo.mHeight, mInfo.mTitle.data(), mIsFullscreen ? mMonitor.mGetMonitor() : nullptr, nullptr);
        if (!mWindow) {
            throw WindowException("Failed to create window!");
        }
    }

    void Window::mLoadGL()
    {
        glfwMakeContextCurrent(mWindow);
        if (!gladLoadGL()) {
            throw WindowException("Failed to load OpenGL!");
        }
    }

    void Window::mRetrieveSize() {
        glfwGetWindowSize(mWindow, &mSize[V2i32::WIDTH], &mSize[V2i32::HEIGHT]);
    }

    void Window::mRetrievePosition() {
        glfwGetWindowPos(mWindow, &mPosition[V2i32::X], &mPosition[V2i32::Y]);
    }

    void Window::mRetrieveFramebufferSize() {
        glfwGetFramebufferSize(mWindow, &mFramebufferSize[V2i32::WIDTH], &mFramebufferSize[V2i32::HEIGHT]);
    }

    void Window::mRetrieveFrameSize()
    {
        glfwGetWindowFrameSize(mWindow, 
            &mFrameSize[V2i32::X], &mFrameSize[V2i32::Y],
            &mFrameSize[V2i32::Z], &mFrameSize[V2i32::W]
        );
    }

    void Window::mRetrieveContentScale() {
        glfwGetWindowContentScale(mWindow, &mContentScale[V2f::WIDTH], &mContentScale[V2f::HEIGHT]);
    }

    void Window::mRetrieveMonitor() {
        mFullscreenMonitor = mMonitor.mGetMonitor();
    }

    void Window::mRetrieveVideoMode() {
        mVidMode = glfwGetVideoMode(mFullscreenMonitor);
    }

    void Window::mInitializeAspectRatio() {
        mAspectRatio = { mSize[V2i32::NUMERATOR], mSize[V2i32::DENOMINATOR] };
    }

    void Window::mInitializeSizeBeforeFullscreen() {
        mSizeBeforeFullscreen = mSize;
    }

    void Window::mInitializePositionBeforeFullscreen() {
        mPositionBeforeFullscreen = mPosition;
    }

} // namespace TIMGE

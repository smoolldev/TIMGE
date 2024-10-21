#include "TIMGE/Window.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <filesystem>
#include <iostream>

#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

namespace TIMGE
{
    Window *Window::mInstance = nullptr;

    Window::Window(Window::Info &info, Monitor& monitor) : mInfo{info}, mMonitor{monitor}, mWindow{nullptr}
    {
        if (mInstance) {
            throw "Only one instance of Window is allowed!\n";
        }

        mInstance = this;

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mInfo.mOpenGLVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mInfo.mOpenGLVersionMinor);

        for (int i = 0; i < sizeof(mWINDOWHINTS) / sizeof(mWINDOWHINTS[0]); i++) {
            glfwWindowHint(mWINDOWHINTS[i], (mInfo.mFlags >> i) & 1);
        }

        mIsFullscreen = mInfo.mIsFullscreen;

        mWindow = glfwCreateWindow(mInfo.mWidth, mInfo.mHeight, mInfo.mTitle.data(), mIsFullscreen ? mMonitor.mGetMonitor() : nullptr, nullptr);
        if (!mWindow) {
            throw "Failed to create window!\n";
        }

        SetIcon(mInfo.mIconPath);

        glfwMakeContextCurrent(mWindow);
        if (!gladLoadGL()) {
            throw "Failed to load OpenGL!\n";
        }

        glfwSetWindowSizeLimits(
            mWindow,
            static_cast<int>((mInfo.mMinWidth == 0) ? GLFW_DONT_CARE : mInfo.mMinWidth),
            static_cast<int>((mInfo.mMinHeight == 0) ? GLFW_DONT_CARE : mInfo.mMinHeight),
            static_cast<int>((mInfo.mMaxWidth == 0) ? GLFW_DONT_CARE : mInfo.mMaxWidth),
            static_cast<int>((mInfo.mMaxHeight == 0) ? GLFW_DONT_CARE : mInfo.mMaxHeight)
        );
    }

    Window::~Window() {
        glfwDestroyWindow(mWindow);
    }

    [[nodiscard]] const V2i32& Window::GetPosition() const {
        return mPosition;
    }

    [[nodiscard]] const V2i32& Window::GetSize() const {
        return mSize;
    }

    [[nodiscard]] const V2i32& Window::GetFramebufferSize() const {
        return mFramebufferSize;
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
            std::cout << "Image at path: " << iconPath << " does not exist.\n";
            std::cout << "Setting icon to OS default..." << "\n";
            glfwSetWindowIcon(mWindow, 0, nullptr);
        }
    }

    void Window::SetPosition(V2i32 position) {
        glfwSetWindowPos(mWindow, position[V2i32::X], position[V2i32::Y]);
    }

    void Window::SetAspectRatio(V2i32 aspectRatio) {
        glfwSetWindowAspectRatio(mWindow, aspectRatio[V2i32::A], aspectRatio[V2i32::B]);
    }

    void Window::SetSize(V2i32 size) {
        glfwSetWindowSize(mWindow, size[V2i32::WIDTH], size[V2i32::HEIGHT]);
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
        GLFWmonitor* monitor = mMonitor.mGetMonitor();

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (!mIsFullscreen)
        {
            mSize = GetSize();
            mPosition = GetPosition();

            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_FALSE);
            SetSize({ mode->width, mode->height} );
            SetPosition({ 0, 0 });
        } else
        {
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_TRUE);
            SetSize({ mSize[V2i32::WIDTH], mSize[V2i32::HEIGHT] });
            SetPosition({ mPosition[V2i32::X], mPosition[V2i32::Y] });
        }

        mIsFullscreen = !mIsFullscreen;
    }

    void Window::Fullscreen()
    {
        GLFWmonitor* monitor = mMonitor.mGetMonitor();

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (!mIsFullscreen)
        {
            mSize = GetSize();
            mPosition = GetPosition();

            glfwSetWindowMonitor(mWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        } else {
            glfwSetWindowMonitor(mWindow, nullptr, mPosition[V2i32::X], mPosition[V2i32::Y], mSize[V2i32::WIDTH], mSize[V2i32::HEIGHT], 0);
        }

        mIsFullscreen = !mIsFullscreen;
    }

    [[nodiscard]] bool Window::ShouldClose() {
        return glfwWindowShouldClose(mWindow);
    }

    GLFWwindow *Window::mGetWindow() {
        return mWindow;
    }
} // namespace TIMGE

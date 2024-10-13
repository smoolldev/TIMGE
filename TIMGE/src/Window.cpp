#include "TIMGE/Window.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

<<<<<<< HEAD
<<<<<<< HEAD
//#define STB_IMAGE_IMPLEMENTATION
=======
>>>>>>> 3ed8b4d (Fix: use new vector template and more)
=======
//#define STB_IMAGE_IMPLEMENTATION
>>>>>>> 976dddf (Fix TIMGESandbox stb_image linker error)
#include <stb_image/stb_image.h>

namespace TIMGE
{
    Window::Window(const Window::Info& info)
     : mInfo{info}, mWindow{nullptr}
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mInfo.mOpenGLVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mInfo.mOpenGLVersionMinor);

        for (int i = 0; i < sizeof(mWINDOWHINTS) / sizeof(mWINDOWHINTS[0]); i++) {
            glfwWindowHint(mWINDOWHINTS[i], (mInfo.mFlags >> i) & 1);
        }

        mIsFullscreen = mInfo.mIsFullscreen;

        mWindow = glfwCreateWindow(mInfo.mWidth, mInfo.mHeight, mInfo.mTitle.data(), mIsFullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
        if (!mWindow) {
            throw "Failed to create window!\n";
        }
        
        SetIcon(mInfo.mIconPath);
        
        glfwMakeContextCurrent(mWindow);
        if (!gladLoadGL()) {
            throw "Failed to load OpenGL!\n";
        }

        glfwSetWindowSizeLimits(mWindow,
            static_cast<int>((mInfo.mMinWidth == 0) ? GLFW_DONT_CARE : mInfo.mMinWidth),
            static_cast<int>((mInfo.mMinHeight == 0) ? GLFW_DONT_CARE : mInfo.mMinHeight),
            static_cast<int>((mInfo.mMaxWidth == 0) ? GLFW_DONT_CARE : mInfo.mMaxWidth),
            static_cast<int>((mInfo.mMaxHeight == 0) ? GLFW_DONT_CARE : mInfo.mMaxHeight)
        );
    }

    Window::~Window() {
        glfwDestroyWindow(mWindow);
    }

    GLFWwindow* Window::GetWindow() {
          return mWindow;
    }

    Vector<int, 2> Window::GetPosition() const
    {
        int x, y;

        glfwGetWindowPos(mWindow, &x, &y);

        return { x, y };
    }

    Vector<int, 2> Window::GetSize() const
    {
        int width, height;

        glfwGetWindowSize(mWindow, &width, &height);

        return { width, height };
    }

    Vector<int, 2> Window::GetFramebufferSize() const
    {
        int width, height;

        glfwGetFramebufferSize(mWindow, &width, &height);

        return { width, height };
    }

    Vector<int, 4> Window::GetFrameSize() const
    {
        int left, top, right, bottom;

        glfwGetWindowFrameSize(mWindow, &left, &top, &right, &bottom);

        return { left, top, right, bottom };
    }

    Vector<float, 2> Window::GetContentScale() const
    {
        float x, y;

        glfwGetWindowContentScale(mWindow, &x, &y);

        return { x, y };
    }

    float Window::GetOpacity() const {
        return glfwGetWindowOpacity(mWindow);
    }

    GLFWmonitor* Window::GetMonitor() const {
        return glfwGetWindowMonitor(mWindow);
    }

    void Window::SetTitle(std::string_view title) {
        glfwSetWindowTitle(mWindow, title.data());
    }

    void Window::SetIcon(std::filesystem::path iconPath)
    {
        if (std::filesystem::exists(iconPath)) {
            GLFWimage image;

            image.pixels = stbi_load(iconPath.string().c_str(), &image.width, &image.height, nullptr, 4);;

            glfwSetWindowIcon(mWindow, 1, &image);

            stbi_image_free(image.pixels);
        } else if (iconPath == "Default") {
            glfwSetWindowIcon(mWindow, 0, nullptr);
        } else {
            std::cout << "Image at path: " << iconPath << " does not exist.\n";
            std::cout << "Setting icon to OS default..." << "\n";
            glfwSetWindowIcon(mWindow, 0, nullptr);
        }
    }

    void Window::SetPosition(int x, int y) {
        glfwSetWindowPos(mWindow, x, y);
    }

    void Window::SetAspectRatio(int numerator, int denominator) {
        glfwSetWindowAspectRatio(mWindow, numerator, denominator);
    }

    void Window::SetSize(int width, int height) {
        glfwSetWindowSize(mWindow, width, height);
    }

    void Window::SetOpacity(float opacity) {
        glfwSetWindowOpacity(mWindow, opacity);
    }

    void Window::SetMonitor(GLFWmonitor* monitor, int x, int y, int width, int height, int refreshRate) {
        glfwSetWindowMonitor(mWindow, monitor, x, y, width, height, refreshRate);
    }

    void Window::Minimize() {
        glfwIconifyWindow(mWindow);
    }

    void Window::Restore() {
        SetSize(mSize[V2i32::WIDTH], mSize[V2i32::HEIGHT]);
        SetPosition(mPosition[V2i32::X], mPosition[V2i32::Y]);

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
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (!mIsFullscreen)
        {
            mSize = GetSize();
            mPosition = GetPosition();

            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_FALSE);
            SetSize(mode->width, mode->height);
            SetPosition(0, 0);
        } else
        {
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_TRUE);
            SetSize(mSize[V2i32::WIDTH], mSize[V2i32::HEIGHT]);
            SetPosition(mPosition[V2i32::X], mPosition[V2i32::Y]);
        }

        mIsFullscreen = !mIsFullscreen;
    }

    void Window::Fullscreen()
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (!mIsFullscreen)
        {
            mSize = GetSize();
            mPosition = GetPosition();

            SetMonitor(monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        } else {
            SetMonitor(nullptr, mPosition[V2i32::X], mPosition[V2i32::Y], mSize[V2i32::WIDTH],mSize[V2i32::HEIGHT], 0);
        }

        mIsFullscreen = !mIsFullscreen;
    }
}

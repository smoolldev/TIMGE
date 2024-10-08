#include "TIMGE/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TIMGE
{
    Window::Window(const WindowInfo& info)
        : mInfo(info),
          mWindow(nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, static_cast<int>(mInfo.openGLVersionMajor));
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, static_cast<int>(mInfo.openGLVersionMinor));
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        for (int i = 0; i < sizeof(mWINDOWHINTS) / sizeof(mWINDOWHINTS[0]); i++) {
            glfwWindowHint(mWINDOWHINTS[i], (mInfo.flags >> i) & 1);
        }

        mWindow = glfwCreateWindow(mInfo.width, mInfo.height, mInfo.title.c_str(), nullptr, nullptr);
        if (!mWindow) {
            throw "Failed to create window";
        }

        glfwSetWindowSizeLimits(
            mWindow,
            static_cast<int>((mInfo.minWidth == 0) ? GLFW_DONT_CARE : mInfo.minWidth),
            static_cast<int>((mInfo.minHeight == 0) ? GLFW_DONT_CARE : mInfo.minHeight),
            static_cast<int>((mInfo.maxWidth == 0) ? GLFW_DONT_CARE : mInfo.maxWidth),
            static_cast<int>((mInfo.maxHeight == 0) ? GLFW_DONT_CARE : mInfo.maxHeight)
        );

        glfwMakeContextCurrent(mWindow);
        if (!gladLoadGL(glfwGetProcAddress)) {
            throw "Failed to initialize GLAD";
        }

        glViewport(0, 0, mInfo.width, mInfo.height);
    }
}

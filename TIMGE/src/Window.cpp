#include "TIMGE/Window.hpp"

#include <glad/glad.h>

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

	mWindow = glfwCreateWindow(mInfo.mWidth, mInfo.mHeight, mInfo.mTitle.data(), nullptr, nullptr);
	if (!mWindow) {
	    throw "Failed to create window!\n";
	}
	
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

    Window::~Window()
    {
        glfwDestroyWindow(mWindow);
    }
    
    GLFWwindow* Window::GetWindow()
    {
	return mWindow;
    }
}

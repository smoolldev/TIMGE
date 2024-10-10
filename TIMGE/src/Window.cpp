#include "TIMGE/Window.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <system_error>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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

		GetSize(mSize.x, mSize.y);
		GetPosition(mPosition.x, mPosition.y);
		
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

	Vector2D<int> Window::GetPosition(int x, int y)
	{
		glfwGetWindowPos(mWindow, &x, &y);

		return { x, y };
	}

	Vector2D<int> Window::GetSize(int width, int height)
	{
		glfwGetWindowSize(mWindow, &width, &height);

		return { width, height };
	}

	Vector2D<int> Window::GetFramebufferSize(int width, int height)
	{
		glfwGetFramebufferSize(mWindow, &width, &height);

		return { width, height };
	}

	Vector4D<int> Window::GetFrameSize(int left, int top, int right, int bottom)
	{
		glfwGetWindowFrameSize(mWindow, &left, &top, &right, &bottom);

		return { left, top, right, bottom };
	}

	Vector2D<float> Window::GetContentScale(float x, float y)
	{
		glfwGetWindowContentScale(mWindow, &x, &y);

		return { x, y };
	}

	float Window::GetOpacity() {
		return glfwGetWindowOpacity(mWindow);
	}

	GLFWmonitor* Window::GetMonitor() {
		return glfwGetWindowMonitor(mWindow);
	}

	int Window::GetAttribute(int attribute) {
		return glfwGetWindowAttrib(mWindow, attribute);
	}

	void* Window::GetUserPointer() {
		return glfwGetWindowUserPointer(mWindow);
	}

	void Window::SetTitle(std::string_view title) {
		glfwSetWindowTitle(mWindow, title.data());
	}

	void Window::SetIcon(std::filesystem::path iconPath)
	{
		if (std::filesystem::exists(iconPath)) {
			int width, height;
			unsigned char* pixels;
			GLFWimage* image[1];

			pixels = stbi_load(iconPath.string().c_str(), &width, &height, nullptr, 4);

			image[0]->width = width;
			image[0]->height = height;
			image[0]->pixels = pixels;

			glfwSetWindowIcon(mWindow, 1, image[0]);

			stbi_image_free(pixels);
		} else if (iconPath == "Default") {
			glfwSetWindowIcon(mWindow, 0, nullptr);
		} else {
			std::cout << "Image at path: " << iconPath << " does not exist\n";
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

	void Window::SetAttribute(int attribute, int value) {
		glfwSetWindowAttrib(mWindow, attribute, value);
	}

	void Window::SetUserPointer(void* pointer) {
		glfwSetWindowUserPointer(mWindow, pointer);
	}

	void Window::Minimize() {
		glfwIconifyWindow(mWindow);
	}

	void Window::Restore() {
		SetSize(mSize.x, mSize.y);
		SetPosition(mPosition.x, mPosition.y);

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
}

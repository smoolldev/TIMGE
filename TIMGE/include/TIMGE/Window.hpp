#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdint>
#include <filesystem>
#include <string_view>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace TIMGE
{
    class Window
    {
	public:
	
	using FLAGS = uint32_t;
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

	struct Info
	{
	    std::string_view mTitle;
	    uint32_t mWidth;
	    uint32_t mHeight;
	    uint32_t mMinWidth;
	    uint32_t mMinHeight;
	    uint32_t mMaxWidth;
	    uint32_t mMaxHeight;
	    uint32_t mOpenGLVersionMajor;
	    uint32_t mOpenGLVersionMinor;
	    FLAGS mFlags;
	    std::filesystem::path mIconPath;
	};

	Window(const Info& info);
	~Window();
	
	GLFWwindow* GetWindow();

	public:
	
	Info mInfo;
	GLFWwindow* mWindow;

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
    };
}
#endif //WINDOW_HPP

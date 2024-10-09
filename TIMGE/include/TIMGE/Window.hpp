#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "TIMGE/Utils/Vector.hpp"
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
			
			GLFWwindow* GetWindow(); //TODO: Move to private and befriend with Application
			Vector2D<int> GetPosition(int x, int y);
			Vector2D<int> GetSize(int width, int height);
			Vector2D<int> GetFramebufferSize(int width, int height);
			Vector4D<int> GetFrameSize(int left, int top, int right, int bottom);
			Vector2D<float> GetContentScale(float x, float y);
			float GetOpacity();
			GLFWmonitor* GetMonitor();
			int GetAttribute(int attribute);
			void* GetUserPointer();

            void SetTitle(std::string_view title);
			void SetWindowIcon(int count, const GLFWimage* images);
			void SetPosition(int x, int y);
			void SetAspectRatio(int numerator, int denominator);
			void SetSize(int width, int height);
			void SetOpacity(float opacity);
			void SetMonitor(GLFWmonitor* monitor, int x, int y, int width, int height, int refreshRate);
			void SetAttribute(int attribute, int value);
			void SetUserPointer(void* pointer);

			void Minimize();
			void Restore();
			void Maximize();
			void Show();
			void Hide();
			void Focus();
			void RequestAttention();

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
		public:
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

			Info mInfo;
			GLFWwindow* mWindow;
    };
}
#endif // WINDOW_HPP

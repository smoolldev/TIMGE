#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Window.hpp"
#include "Utils/Vector.hpp"
#include "Callback.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Monitor.hpp"

#include <chrono>
#include <cstdint>
#include <string_view>

#ifdef TIMGE_ENABLE_IMGUI
#include <imgui_internal.h>
#endif // TIMGE_ENABLE_IMGUI

namespace TIMGE
{
	class ApplicationBaseException : public Exception
    {
        public:
            ApplicationBaseException(std::string message);
    };

    class ApplicationBase
    {
		public:
		    ApplicationBase();
		    virtual ~ApplicationBase() = 0;
		    virtual void Run() = 0;
		    virtual void Update() = 0;
		    virtual void Render() = 0;
    };

	class ApplicationException : public Exception
    {
        public:
            ApplicationException(std::string message);
    };


    class Application : public ApplicationBase
    {
		private:
			using EventProcessor_T = decltype(&glfwPollEvents);
			using GetTime_T = decltype(&glfwGetTime);
			using SetTime_T = decltype(&glfwSetTime);
		protected:
		    static EventProcessor_T PollEvents;
		    static EventProcessor_T WaitEvents;
			static GetTime_T GetTime;
			static SetTime_T SetTime;
		public:
		    struct Info
		    {
		        Window::Info mWindowInfo;
				V4f mBackground;
				Mouse::Info mMouseInfo;
			    Callback::Callbacks mCallbacks;
		    };

		    Application(const Info& info);
		    Application(std::string_view title, uint32_t width, uint32_t height);
		    virtual ~Application() = 0;

		    virtual void Run() = 0;
		    virtual void Update() = 0;
		    virtual void Render() = 0;

		    virtual void BeginFrame();
		    virtual void EndFrame();

			void SetMonitor(const Monitor& monitor);
			void SetBackgroundColor(const V4f& backgroundColor = { });
			void SetEventProcessor(EventProcessor_T eventProcessor);

			[[nodiscard]] Monitor& GetMonitor();
		    [[nodiscard]] Window& GetWindow();
			[[nodiscard]] Mouse& GetMouse();
			[[nodiscard]] Keyboard& GetKeyboard();
			[[nodiscard]] const double& GetDeltaTime();
			[[nodiscard]] const V4f& GetBackgroundColor();
			[[nodiscard]] EventProcessor_T GetEventProcessor();

			#ifdef TIMGE_ENABLE_IMGUI
			[[nodiscard]] ImGuiContext* GetImGuiContext();
			#endif // TIMGE_ENABLE_IMGUI
		private:
			Info mInfo;
		    Monitor mMonitor;
		    Window mWindow;
			Mouse mMouse;
			Keyboard mKeyboard;

			std::chrono::steady_clock mSteadyClock;

			double mDeltaTime;
			std::chrono::steady_clock::time_point mStartTime;

			EventProcessor_T mEventProcessor;
			
			#ifdef TIMGE_ENABLE_IMGUI
			ImGuiContext* mImGuiContext;
			#endif // TIMGE_ENABLE_IMGUI

		    [[nodiscard]] static Application* mGetInstance();

			static void mConnectMonitor(GLFWmonitor* monitor);
			static void mDisconnectMonitor(GLFWmonitor* monitor);

			void mSetCursorPosition(const V2d& cursorPosition);
			void mSetScrollOffset(const V2d& cursorScrollOffset);

			void mSetPosition(const V2i32& position);
			void mSetSize(const V2ui32& size);
			void mSetFramebufferSize(const V2ui32& framebufferSize);
    	    void mSetFrameSize(const V4ui32& frameSize);
			void mSetContentScale(const V2f& contentScale);

			static Application* mInstance;

		    friend void Callback::ErrorCallback(int errorCode, const char* description);
    	    friend void Callback::WindowPosCallback(GLFWwindow* window, int xPos, int yPos);
    	    friend void Callback::WindowSizeCallback(GLFWwindow* window, int width, int height);
    	    friend void Callback::WindowCloseCallback(GLFWwindow* window);
		    friend void Callback::WindowRefreshCallback(GLFWwindow *window);
    	    friend void Callback::WindowFocusCallback(GLFWwindow* window, int focused);
    	    friend void Callback::WindowIconifyCallback(GLFWwindow* window, int iconified);
    	    friend void Callback::WindowMaximizeCallback(GLFWwindow* window, int maximized);
    	    friend void Callback::FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    	    friend void Callback::WindowContentScaleCallback(GLFWwindow* window, float xScale, float yScale);
    	    friend void Callback::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    	    friend void Callback::CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
    	    friend void Callback::CursorEnterCallback(GLFWwindow* window, int entered);
    	    friend void Callback::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    	    friend void Callback::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    	    friend void Callback::CharCallback(GLFWwindow* window, unsigned int codepoint);
    	    friend void Callback::CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
    	    friend void Callback::DropCallback(GLFWwindow* window, int pathCount, const char* path[]);
    	    friend void Callback::MonitorCallback(GLFWmonitor* monitor, int event);
    	    friend void Callback::JoystickCallback(int jid, int event);
	};
}

#endif //APPLICATION_HPP

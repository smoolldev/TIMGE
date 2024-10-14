#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "TIMGE/Window.hpp"
#include "TIMGE/Utils/Vector.hpp"
#include "TIMGE/CallbackDefs.hpp"

#include <cstdint>
#include <string_view>

namespace TIMGE
{
    class ApplicationBase
    {
	public:
	    ApplicationBase();
	    virtual ~ApplicationBase() = 0;
	    virtual void Run() = 0;
	    virtual void Update() = 0;
	    virtual void Render() = 0;
    };

    class Application : public ApplicationBase
    {
	public:
	    struct Info
	    {
	        Window::Info mWindowInfo; // TODO: Change Window class
	        Vector<float, 4> mBackground;
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

	    bool WindowShouldClose();
	    Window& GetWindow();
	private:
	    using EventProcessing_T = void(*)();
	protected:
	    static EventProcessing_T PollEvents;
	    static EventProcessing_T WaitEvents;
	private:
	    Info mInfo;
	    Window mWindow;
	    static Application* mInstance;

	    static Application* GetInstance(); 
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

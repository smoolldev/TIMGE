#include "TIMGE/Application.hpp"
#include "TIMGE/CallbackDefs.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TIMGE
{
    ApplicationBase::ApplicationBase()
    {
        if (!glfwInit()) {
	   throw "Failed to initialize GLFW!\n";
        }
    }

    ApplicationBase::~ApplicationBase() {
        glfwTerminate();
    }

    Application::Application(Info info)
     : ApplicationBase(),
       mInfo{info},
       mMonitor{*Monitor::GetPrimaryMonitor()},
       mWindow{info.mWindowInfo},
       mMouse{info.mMouseInfo, mWindow},
       mKeyboard{mWindow},
       mDeltaTime{0},
       window{mWindow},
       mouse{mMouse},
       keyboard{mKeyboard},
       deltaTime{GetDeltaTime()},
       windowPosition{mWindow.GetPosition()},
       windowSize{mWindow.GetSize()},
       windowFramebufferSize{mWindow.GetFramebufferSize()},
       windowFrameSize{mWindow.GetFrameSize()},
       windowContentScale{mWindow.GetContentScale()},
       cursorPosition{mMouse.GetPosition()},
       cursorScrollOffset{mMouse.GetOffset()}
    {
        if (Application::mInstance) {
            throw "Only one instance of Application is allowed!\n";
        }
        mInstance = this;

        glfwSetErrorCallback(Callback::ErrorCallback);
        glfwSetWindowPosCallback(mWindow.GetWindow(), Callback::WindowPosCallback);
        glfwSetWindowSizeCallback(mWindow.GetWindow(), Callback::WindowSizeCallback);
        glfwSetWindowCloseCallback(mWindow.GetWindow(), Callback::WindowCloseCallback);
        glfwSetWindowRefreshCallback(mWindow.GetWindow(), Callback::WindowRefreshCallback);
        glfwSetWindowFocusCallback(mWindow.GetWindow(), Callback::WindowFocusCallback);
        glfwSetWindowIconifyCallback(mWindow.GetWindow(), Callback::WindowIconifyCallback);
        glfwSetWindowMaximizeCallback(mWindow.GetWindow(), Callback::WindowMaximizeCallback);
        glfwSetFramebufferSizeCallback(mWindow.GetWindow(), Callback::FramebufferSizeCallback);
        glfwSetWindowContentScaleCallback(mWindow.GetWindow(), Callback::WindowContentScaleCallback);
        glfwSetMouseButtonCallback(mWindow.GetWindow(), Callback::MouseButtonCallback);
        glfwSetCursorPosCallback(mWindow.GetWindow(), Callback::CursorPosCallback);
        glfwSetCursorEnterCallback(mWindow.GetWindow(), Callback::CursorEnterCallback);
        glfwSetScrollCallback(mWindow.GetWindow(), Callback::ScrollCallback);
        glfwSetKeyCallback(mWindow.GetWindow(), Callback::KeyCallback);
        glfwSetCharCallback(mWindow.GetWindow(), Callback::CharCallback);
        glfwSetCharModsCallback(mWindow.GetWindow(), Callback::CharModsCallback);
        glfwSetDropCallback(mWindow.GetWindow(), Callback::DropCallback);
        glfwSetMonitorCallback(Callback::MonitorCallback);
        glfwSetJoystickCallback(Callback::JoystickCallback);
    }

    Application::Application(std::string_view title, uint32_t width, uint32_t height)
     : Application(
        Application::Info{
            Window::Info{
    	        title,
    	        width,
    	        height,
    	        0, 0, 0, 0,
    	        4, 6,
    	        Window::RESIZABLE | Window::VISIBLE | Window::DECORATED |
    	        Window::FOCUSED | Window::AUTO_ICONIFY | Window::CENTER_CURSOR |
    	        Window::FOCUS_ON_SHOW,
    	        "Default",
                false
    	    },
            Mouse::Info{},
            Vector<float, 4>{0.0f, 0.0f, 0.0f, 1.0f},
            Callback::Callbacks{}
        }
    )
    {}

    Application::~Application()
    {}

    void Application::BeginFrame()
    {
        mStartTime = GetTime();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(
            mInfo.mBackground[V4f::R], 
            mInfo.mBackground[V4f::G], 
            mInfo.mBackground[V4f::B], 
            mInfo.mBackground[V4f::A] 
        );
    }

    void Application::EndFrame()
    {
        mDeltaTime = GetTime() - mStartTime;

        PollEvents();

        glfwSwapBuffers(mWindow.GetWindow());
    }

    Window& Application::GetWindow() {
        return mWindow;
    }

    Mouse& Application::GetMouse() {
        return mMouse;
    }

    Keyboard& Application::GetKeyboard() {
        return mKeyboard;
    }

    const Application::Time& Application::GetDeltaTime() {
        return mDeltaTime;
    }

    Application* Application::GetInstance() {
        return Application::mInstance;
    }

    void Application::mSetCursorPosition(double xPosition, double yPosition) {
        mMouse.mPosition = { xPosition, yPosition };
    }

    void Application::mSetScrollOffset(double xOffset, double yOffset) {
        mMouse.mOffset = { xOffset, yOffset };
    }

    void Application::mSetPosition(int x, int y) {
        mWindow.mPosition = { x, y };
    }

	void Application::mSetSize(int width, int height) {
        mWindow.mSize = { width, height };
    }

	void Application::mSetFramebufferSize(int width, int height) {
       mWindow.mFramebufferSize = { width, height }; 
    }

    void Application::mSetFrameSize(int top, int left, int right, int bottom) {
        mWindow.mFrameSize = { top, left, right, bottom };
    }

	void Application::mSetContentScale(float xScale, float yScale) {
        mWindow.mContentScale = { xScale, yScale };
    }

    void Application::mConnectMonitor(GLFWmonitor* monitor) {
        Monitor::Connect(monitor);
    }

	void Application::mDisconnectMonitor(GLFWmonitor* monitor) {
        Monitor::Disconnect(monitor);
    }

    Application::EventProcessing_T Application::PollEvents = &glfwPollEvents;
    Application::EventProcessing_T Application::WaitEvents = &glfwWaitEvents;

    Application::GetTime_T Application::GetTime = &glfwGetTime;
    Application::SetTime_T Application::SetTime = &glfwSetTime;

    Application* Application::mInstance = nullptr;
}

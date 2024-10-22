#include "TIMGE/Application.hpp"
#include "TIMGE/CallbackDefs.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <GLFW/glfw3.h>
#include <format>

namespace TIMGE
{
    ApplicationBaseException::ApplicationBaseException(std::string message)
     : Exception(std::format("ApplicationBase: {}", message))
    {}

    ApplicationBase::ApplicationBase()
    {
        if (!glfwInit()) {
	        throw ApplicationBaseException("Failed to initialize GLFW!");
        }
    }

    ApplicationBase::~ApplicationBase() {
        glfwTerminate();
    }

    ApplicationException::ApplicationException(std::string message)
     : Exception(std::format("Application: {}", message))
    {}

    Application::EventProcessor_T Application::PollEvents = &glfwPollEvents;
    Application::EventProcessor_T Application::WaitEvents = &glfwWaitEvents;

    Application::GetTime_T Application::GetTime = &glfwGetTime;
    Application::SetTime_T Application::SetTime = &glfwSetTime;

    Application* Application::mInstance = nullptr;

    Application::Application(const Info& info)
     : ApplicationBase(),
       mInfo{info},
       mMonitor{Monitor::GetPrimaryMonitor()},
       mWindow{mInfo.mWindowInfo, mMonitor},
       mMouse{info.mMouseInfo, mWindow},
       mKeyboard{mWindow},
       mDeltaTime{0},
       mStartTime{0},
       mEventProcessor{PollEvents},
       monitor{mMonitor},
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
            throw ApplicationException("Only one instance of Application is allowed!");
        }
        mInstance = this;

        glfwSetErrorCallback(Callback::ErrorCallback);
        glfwSetWindowPosCallback(mWindow.mGetWindow(), Callback::WindowPosCallback);
        glfwSetWindowSizeCallback(mWindow.mGetWindow(), Callback::WindowSizeCallback);
        glfwSetWindowCloseCallback(mWindow.mGetWindow(), Callback::WindowCloseCallback);
        glfwSetWindowRefreshCallback(mWindow.mGetWindow(), Callback::WindowRefreshCallback);
        glfwSetWindowFocusCallback(mWindow.mGetWindow(), Callback::WindowFocusCallback);
        glfwSetWindowIconifyCallback(mWindow.mGetWindow(), Callback::WindowIconifyCallback);
        glfwSetWindowMaximizeCallback(mWindow.mGetWindow(), Callback::WindowMaximizeCallback);
        glfwSetFramebufferSizeCallback(mWindow.mGetWindow(), Callback::FramebufferSizeCallback);
        glfwSetWindowContentScaleCallback(mWindow.mGetWindow(), Callback::WindowContentScaleCallback);
        glfwSetMouseButtonCallback(mWindow.mGetWindow(), Callback::MouseButtonCallback);
        glfwSetCursorPosCallback(mWindow.mGetWindow(), Callback::CursorPosCallback);
        glfwSetCursorEnterCallback(mWindow.mGetWindow(), Callback::CursorEnterCallback);
        glfwSetScrollCallback(mWindow.mGetWindow(), Callback::ScrollCallback);
        glfwSetKeyCallback(mWindow.mGetWindow(), Callback::KeyCallback);
        glfwSetCharCallback(mWindow.mGetWindow(), Callback::CharCallback);
        glfwSetCharModsCallback(mWindow.mGetWindow(), Callback::CharModsCallback);
        glfwSetDropCallback(mWindow.mGetWindow(), Callback::DropCallback);
        glfwSetMonitorCallback(Callback::MonitorCallback);
        glfwSetJoystickCallback(Callback::JoystickCallback);
    }

    Application::Application(std::string_view title, uint32_t width, uint32_t height)
     : Application(
        Application::Info {
            Window::Info {
    	        title,
    	        width,
    	        height,
    	        0, 0, 0, 0,
    	        4, 6,
    	        Window::RESIZABLE | Window::VISIBLE | Window::DECORATED |
    	        Window::FOCUSED | Window::AUTO_ICONIFY | Window::CENTER_CURSOR |
    	        Window::FOCUS_ON_SHOW,
                false,
    	    },
            Vector<float, 4> { 0.0f, 0.0f, 0.0f, 1.0f },
            Mouse::Info {},
            Callback::Callbacks {}
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

        mEventProcessor();

        glfwSwapBuffers(mWindow.mGetWindow());
    }

    void Application::SetMonitor(const Monitor& monitor) {
        mMonitor = monitor;
    }

    void Application::SetBackgroundColor(const V4f& backgroundColor) {
        mInfo.mBackground = backgroundColor;
    }

    void Application::SetEventProcessor(EventProcessor_T eventProcessor) {
        mEventProcessor = eventProcessor;
    }

    [[nodiscard]] Window& Application::GetWindow() {
        return mWindow;
    }

    [[nodiscard]] Mouse& Application::GetMouse() {
        return mMouse;
    }

    [[nodiscard]] Keyboard& Application::GetKeyboard() {
        return mKeyboard;
    }

    [[nodiscard]] const Time& Application::GetDeltaTime() {
        return mDeltaTime;
    }

    [[nodiscard]] const V4f& Application::GetBackgroundColor() {
        return mInfo.mBackground;
    }

    [[nodiscard]] Application* Application::mGetInstance() {
        return Application::mInstance;
    }

    void Application::mConnectMonitor(GLFWmonitor* monitor) {
        Monitor::mConnect(monitor);
    }

	void Application::mDisconnectMonitor(GLFWmonitor* monitor) {
        Monitor::mDisconnect(monitor);
    }

    void Application::mSetCursorPosition(const V2d& cursorPosition) {
        mMouse.mPosition = cursorPosition;
    }

    void Application::mSetScrollOffset(const V2d& cursorScrollOffset) {
        mMouse.mOffset = cursorScrollOffset;
    }

    void Application::mSetPosition(const V2i32& position) {
        mWindow.mPosition = position;
    }

	void Application::mSetSize(const V2i32& size) {
        mWindow.mSize = size;
    }

	void Application::mSetFramebufferSize(const V2i32& framebufferSize) {
       mWindow.mFramebufferSize = framebufferSize; 
    }

    void Application::mSetFrameSize(const V4i32& frameSize) {
        mWindow.mFrameSize = frameSize;
    }

	void Application::mSetContentScale(const V2f& contentScale) {
        mWindow.mContentScale = contentScale;
    }
}

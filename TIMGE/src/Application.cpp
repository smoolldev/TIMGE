#include "TIMGE/Application.hpp"
#include "TIMGE/CallbackDefs.hpp"

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
     : ApplicationBase(), mInfo{info}, mWindow{info.mWindowInfo}, mMosue{info.mMouseInfo, mWindow}, mKeybaord{mWindow}
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
        PollEvents();
        glfwSwapBuffers(mWindow.GetWindow());
    }

    Window& Application::GetWindow() {
        return mWindow;
    }

    Mouse& Application::GetMouse() {
        return mMosue;
    }

    Keyboard& Application::GetKeyboard() {
        return mKeybaord;
    }

    Application* Application::GetInstance() {
        return Application::mInstance;
    }

    void Application::mSetCursorPosition(double xPosition, double yPosition) {
        mMosue.mPosition = { xPosition, yPosition };
    }

    void Application::mSetScrollOffset(double xOffset, double yOffset) {
        mMosue.mOffset = { xOffset, yOffset };
    }

    Application::EventProcessing_T Application::PollEvents = &glfwPollEvents;
    Application::EventProcessing_T Application::WaitEvents = &glfwWaitEvents;
    Application* Application::mInstance = nullptr;
}

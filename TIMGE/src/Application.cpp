#include "TIMGE/Application.hpp"
#include "TIMGE/Callback.hpp"
#include "TIMGE/Utils/Vector.hpp"
#include "TIMGE/Window.hpp"

#include <format>

#ifdef TIMGE_ENABLE_IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#endif //TIMGE_ENABLE_IMGUI

namespace TIMGE
{
    ApplicationBaseException::ApplicationBaseException(const std::string& message)
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

    ApplicationException::ApplicationException(const std::string& message)
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
       mDeltaTime{},
       mStartTime{std::chrono::steady_clock::now()},
       mEventProcessor{PollEvents}
    {
        if (Application::mInstance) {
            throw ApplicationException("Only one instance of Application is allowed!");
        }
        mInstance = this;

        #ifdef TIMGE_ENABLE_IMGUI
            IMGUI_CHECKVERSION();
            mImGuiContext = ImGui::CreateContext();
            ImGui_ImplGlfw_InitForOpenGL(mWindow.mGetWindow(), false);
            std::string glsl_version = std::format(
                "#version {}{}0 core", 
                mInfo.mWindowInfo.mOpenGLVersion[V2ui32::GL_MAJOR], 
                mInfo.mWindowInfo.mOpenGLVersion[V2ui32::GL_MINOR]
            );
            ImGui_ImplOpenGL3_Init(glsl_version.c_str());
        #endif // TIMGE_ENABLE_IMGUI

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
                V2ui32{width, height},
    	        V4ui32{0, 0, 0, 0},
                V2i32{POSITION_DONT_CARE, POSITION_DONT_CARE},
                V2ui32{ASPECT_RATIO_DONT_CARE, ASPECT_RATIO_DONT_CARE},
                1.0f,
    	        V2ui32{4, 6},
    	        Window::RESIZABLE | Window::VISIBLE | Window::DECORATED |
    	        Window::FOCUSED | Window::AUTO_ICONIFY | Window::CENTER_CURSOR |
    	        Window::FOCUS_ON_SHOW,
    	    },
            Vector<float, 4> { 0.0f, 0.0f, 0.0f, 1.0f },
            Mouse::Info {},
            Callback::Callbacks {}
        }
    )
    {}

    Application::~Application()
    {
        #ifdef TIMGE_ENABLE_IMGUI
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        #endif // TIMGE_ENABLE_IMGUI
    }

    void Application::BeginFrame()
    {
        mStartTime = mSteadyClock.now();

        glClearColor(
            mInfo.mBackground[V4f::R], 
            mInfo.mBackground[V4f::G], 
            mInfo.mBackground[V4f::B], 
            mInfo.mBackground[V4f::A] 
        );
        glClear(GL_COLOR_BUFFER_BIT);

        #ifdef TIMGE_ENABLE_IMGUI
            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();
        #endif // TIMGE_ENABLE_IMGUI
    }

    void Application::EndFrame()
    {
        #ifdef TIMGE_ENABLE_IMGUI
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        #endif // TIMGE_ENABLE_IMGUI

        mEventProcessor();
        glfwSwapBuffers(mWindow.mGetWindow());

        mDeltaTime = std::chrono::nanoseconds(mSteadyClock.now() - mStartTime).count() * 1.0E-9;
    }

    void Application::SetMonitor(const Monitor& monitor) {
        mMonitor = monitor;
        mWindow.mUpdateMonitor();
    }

    void Application::SetBackgroundColor(const V4f& backgroundColor) {
        mInfo.mBackground = backgroundColor;
    }

    void Application::SetEventProcessor(EventProcessor_T eventProcessor) {
        mEventProcessor = eventProcessor;
    }

    [[nodiscard]] Monitor& Application::GetMonitor() {
        return mMonitor;
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

    [[nodiscard]] const double& Application::GetDeltaTime() {
        return mDeltaTime;
    }

    [[nodiscard]] const V4f& Application::GetBackgroundColor() {
        return mInfo.mBackground;
    }

    [[nodiscard]] Application::EventProcessor_T Application::GetEventProcessor() {
        return mEventProcessor;
    }

#ifdef TIMGE_ENABLE_IMGUI
    [[nodiscard]] ImGuiContext* Application::GetImGuiContext() {
        return mImGuiContext;
    }
#endif // TIMGE_ENABLE_IMGUI

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
        mWindow.mInfo.mPosition = position;
    }

	void Application::mSetSize(const V2ui32& size) {
        mWindow.mInfo.mSize = size;
    }

	void Application::mSetFramebufferSize(const V2ui32& framebufferSize) {
       mWindow.mFramebufferSize = framebufferSize; 
    }

    void Application::mSetFrameSize(const V4ui32& frameSize) {
        mWindow.mFrameSize = frameSize;
    }

	void Application::mSetContentScale(const V2f& contentScale) {
        mWindow.mContentScale = contentScale;
    }
}

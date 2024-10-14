#include "TIMGE/CallbackDefs.hpp"
#include "TIMGE/Application.hpp"

namespace TIMGE::Callback
{
    void ErrorCallback(int errorCode, const char* description)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mError; func != nullptr) {
            func(errorCode, description);
        }
    }
    void WindowPosCallback(GLFWwindow* window, int xPos, int yPos)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowPos; func != nullptr) {
            func(xPos, yPos);
        }
    }
    void WindowSizeCallback(GLFWwindow* window, int width, int height)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowSize; func != nullptr) {
            func(width, height);
        }
    }
    void WindowCloseCallback(GLFWwindow* window)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowClose; func != nullptr) {
            func();
        }
    }
    void WindowRefreshCallback(GLFWwindow* window)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowRefresh; func != nullptr) {
            func();
        }
    }
    void WindowFocusCallback(GLFWwindow* window, int focused)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowFocus; func != nullptr) {
            func(focused);
        }
    }
    void WindowIconifyCallback(GLFWwindow* window, int iconified)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowIconify; func != nullptr) {
            func(iconified);
        }
    }
    void WindowMaximizeCallback(GLFWwindow* window, int maximized)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowMaximize; func != nullptr) {
            func(maximized);
        }
    }
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mFramebufferSize; func != nullptr) {
            func(width, height);
        }
    }
    void WindowContentScaleCallback(GLFWwindow* window, float xScale, float yScale)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mWindowContentScale; func != nullptr) {
            func(xScale, yScale);
        }
    }
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mMouseButton; func != nullptr) {
            func(button, action, mods);
        }
    }
    void CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mCursorPos; func != nullptr) {
            func(xPos, yPos);
        }
    }
    void CursorEnterCallback(GLFWwindow* window, int entered)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mCursorEnter; func != nullptr) {
            func(entered);
        }
    }
    void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mScroll; func != nullptr) {
            func(xOffset, yOffset);
        }
    }
    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mKey; func != nullptr) {
            func(key, scancode, action, mods);
        }
    }
    void CharCallback(GLFWwindow* window, unsigned int codepoint)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mChar; func != nullptr) {
            func(codepoint);
        }
    }
    void CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mCharmods; func != nullptr) {
            func(codepoint, mods);
        }
    }
    void DropCallback(GLFWwindow* window, int pathCount, const char* path[])
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mDrop; func != nullptr) {
            func(pathCount, path);
        }
    }
    void MonitorCallback(GLFWmonitor* monitor, int event)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mMonitor; func != nullptr) {
            func(event);
        }
    }
    void JoystickCallback(int jid, int event)
    {
        Application* app = Application::GetInstance();
        if (auto func = app->mInfo.mCallbacks.mJoystick; func != nullptr) {
            func(jid, event);
        }
    }
}

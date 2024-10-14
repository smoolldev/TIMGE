#ifndef CALLBACKDEFS_HPP
#define CALLBACKDEFS_HPP

#include <GLFW/glfw3.h>

namespace TIMGE::Callback
{
    using Error_t = void (*)(int errorCode, const char* description);
    using WindowPos_t = void (*)(int xPos, int yPos);
    using WindowSize_t = void (*)(int width, int height);
    using WindowClose_t = void (*)();
    using WindowRefresh_t = void (*)();
    using WindowFocus_t = void (*)(int focused);
    using WindowIconify_t = void (*)(int iconified);
    using WindowMaximize_t = void (*)(int maximized);
    using FramebufferSize_t = void (*)(int width, int height);
    using WindowContentScale_t = void (*)(float xScale, float yScale);
    using MouseButton_t = void (*)(int button, int action, int mods);
    using CursorPos_t = void (*)(double xPos, double yPos);
    using CursorEnter_t = void (*)(int entered);
    using Scroll_t = void (*)(double xOffset, double yOffset);
    using Key_t = void (*)(int key, int scancode, int action, int mods);
    using Char_t = void (*)(unsigned int codepoint);
    using Charmods_t = void (*)(unsigned int codepoint, int mods);
    using Drop_t = void (*)(int pathCount, const char* paths[]);
    using Monitor_t = void (*)(int event);
    using Joystick_t = void (*)(int jid, int event);

    using timgeError_t = void (*)(int errorCode, const char* description);
    using timgeWindowPos_t = void (*)(GLFWwindow* window, int xPos, int yPos);
    using timgeWindowSize_t = void (*)(GLFWwindow* window, int width, int height);
    using timgeWindowClose_t = void (*)(GLFWwindow* window);
    using timgeWindowRefresh_t = void (*)(GLFWwindow* window);
    using timgeWindowFocus_t = void (*)(GLFWwindow* window, int focused);
    using timgeWindowIconify_t = void (*)(GLFWwindow* window, int iconified);
    using timgeWindowMaximize_t = void (*)(GLFWwindow* window, int maximized);
    using timgeFramebufferSize_t = void (*)(GLFWwindow* window, int width, int height);
    using timgeWindowContentScale_t = void (*)(GLFWwindow* window, float xScale, float yScale);
    using timgeMouseButton_t = void (*)(GLFWwindow* window, int button, int action, int mods);
    using timgeCursorPos_t = void (*)(GLFWwindow* window, double xPos, double yPos);
    using timgeCursorEnter_t = void (*)(GLFWwindow* window, int entered);
    using timgeScroll_t = void (*)(GLFWwindow* window, double xOffset, double yOffset);
    using timgeKey_t = void (*)(GLFWwindow* window, int key, int scancode, int action, int mods);
    using timgeChar_t = void (*)(GLFWwindow* window, unsigned int codepoint);
    using timgeCharmods_t = void (*)(GLFWwindow* window, unsigned int codepoint, int mods);
    using timgeDrop_t = void (*)(GLFWwindow* window, int pathCount, const char* paths[]);
    using timgeMonitor_t = void (*)(GLFWmonitor* monitor, int event);
    using timgeJoystick_t = void (*)(int jid, int event);

    void ErrorCallback(int errorCode, const char* description);
    void WindowPosCallback(GLFWwindow* window, int xPos, int yPos);
    void WindowSizeCallback(GLFWwindow* window, int width, int height);
    void WindowCloseCallback(GLFWwindow* window);
    void WindowRefreshCallback(GLFWwindow* window);
    void WindowFocusCallback(GLFWwindow* window, int focused);
    void WindowIconifyCallback(GLFWwindow* window, int iconified);
    void WindowMaximizeCallback(GLFWwindow* window, int maximized);
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void WindowContentScaleCallback(GLFWwindow* window, float xScale, float yScale);
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
    void CursorEnterCallback(GLFWwindow* window, int entered);
    void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void CharCallback(GLFWwindow* window, unsigned int codepoint);
    void CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
    void DropCallback(GLFWwindow* window, int pathCount, const char* path[]);
    void MonitorCallback(GLFWmonitor* monitor, int event);
    void JoystickCallback(int jid, int event);

    struct Callbacks
    {
        Error_t mError;
        WindowPos_t mWindowPos;
        WindowSize_t mWindowSize;
        WindowClose_t mWindowClose;
        WindowRefresh_t mWindowRefresh;
        WindowFocus_t mWindowFocus;
        WindowIconify_t mWindowIconify;
        WindowMaximize_t mWindowMaximize;
        FramebufferSize_t mFramebufferSize;
        WindowContentScale_t mWindowContentScale;
        MouseButton_t mMouseButton;
        CursorPos_t mCursorPos;
        CursorEnter_t mCursorEnter;
        Scroll_t mScroll;
        Key_t mKey;
        Char_t mChar;
        Charmods_t mCharmods;
        Drop_t mDrop;
        Monitor_t mMonitor;
        Joystick_t mJoystick;
    };
}
#endif // CALLBACKDEFS_HPP

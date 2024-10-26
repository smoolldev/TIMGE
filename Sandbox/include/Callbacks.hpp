#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <TIMGE/TIMGE.hpp>

void ErrorCallback(int errorCode, std::string_view description);
void WindowPosCallback(const TIMGE::V2i32& position);
void WindowSizeCallback(const TIMGE::V2ui32& size);
void WindowCloseCallback();
void WindowRefreshCallback();
void WindowFocusCallback(bool focused);
void WindowIconifyCallback(bool iconified);
void WindowMaximizeCallback(bool maximized);
void FramebufferSizeCallback(const TIMGE::V2ui32& framebufferSize);
void WindowContentScaleCallback(const TIMGE::V2f& contentScale);
void MouseButtonCallback(TIMGE::Button button, TIMGE::Mouse::Action action, TIMGE::Modifier mods);
void CursorPosCallback(const TIMGE::V2d& cursorPosition);
void CursorEnterCallback(bool entered);
void ScrollCallback(const TIMGE::V2d& cursorScrollOffset);
void KeyCallback(TIMGE::Key key, int scancode, TIMGE::Keyboard::Action action, TIMGE::Modifier mods);
void CharCallback(unsigned int codepoint);
void CharmodsCallback(unsigned int codepoint, int mods);
void DropCallback(int pathCount, const char* paths[]);
void MonitorCallback(int event);
void JoystickCallback(int jid, int event);

#endif //CALLBACKS_HPP

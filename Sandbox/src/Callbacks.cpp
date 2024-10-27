#include "Callbacks.hpp"
#include "Game.hpp"
#include "TIMGE/Keyboard.hpp"

void ErrorCallback(int errorCode, std::string_view description)
{

}

void WindowPosCallback(const TIMGE::V2i32& position)
{

}

void WindowSizeCallback(const TIMGE::V2ui32& size)
{

}

void WindowCloseCallback()
{

}

void WindowRefreshCallback()
{

}

void WindowFocusCallback(bool focused)
{

}

void WindowIconifyCallback(bool iconified)
{

}

void WindowMaximizeCallback(bool maximized)
{

}

void FramebufferSizeCallback(const TIMGE::V2ui32& framebufferSize)
{

}

void WindowContentScaleCallback(const TIMGE::V2f& contentScale)
{

}


void MouseButtonCallback(TIMGE::Button button, TIMGE::Mouse::Action action, TIMGE::Modifier mods)
{

}

void CursorPosCallback(const TIMGE::V2d& cursorPosition)
{

}

void CursorEnterCallback(bool entered)
{

}

void ScrollCallback(const TIMGE::V2d& cursorScrollOffset)
{

}

void KeyCallback(TIMGE::Key key, int scancode, TIMGE::Keyboard::Action action, TIMGE::Modifier mods)
{
    Game* game = Game::GetInstance();
    TIMGE::Window& window = game->GetWindow();
    TIMGE::Keyboard& keyboard = game->GetKeyboard();
    TIMGE::Mouse& mouse = game->GetMouse();
    auto cursors = mouse.GetCursors();

    if (key == TIMGE::Key::ESCAPE && action == TIMGE::Keyboard::Action::PRESSED) {
        window.SetShouldClose(true);
    }

    if (key == TIMGE::Key::M && action == TIMGE::Keyboard::Action::PRESSED) {
        window.Minimize();
    }

    if (key == TIMGE::Key::R && action == TIMGE::Keyboard::Action::PRESSED) {
        window.Restore();
    }

    if (key == TIMGE::Key::M && mods == TIMGE::Modifier::SHIFT && action == TIMGE::Keyboard::Action::PRESSED) {
        window.Maximize();
    }

    if (key == TIMGE::Key::S && action == TIMGE::Keyboard::Action::PRESSED) {
        window.Show();
    }

    if (key == TIMGE::Key::S && mods == TIMGE::Modifier::SHIFT && action == TIMGE::Keyboard::Action::PRESSED) {
        window.Hide();
    }

    if (key == TIMGE::Key::F11 && action == TIMGE::Keyboard::Action::PRESSED) {
        window.Fullscreen();
    }

    if (key == TIMGE::Key::F11 && mods == TIMGE::Modifier::CONTROL && action == TIMGE::Keyboard::Action::PRESSED) {
        window.BorderlessFullscreen();
    }
}

void CharCallback(unsigned int codepoint)
{

}

void CharmodsCallback(unsigned int codepoint, int mods)
{

}

void DropCallback(int pathCount, const char* path[]) {
    printf("Paths: %d\n\n", pathCount);

    for (int i = 0; i < pathCount; i++) {
        printf("Path: %s\n", path[i]);
    }
}

void MonitorCallback(int event)
{

}


void JoystickCallback(int jid, int event)
{

}

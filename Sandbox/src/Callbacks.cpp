#include "Callbacks.hpp"
#include "Game.hpp"

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

    if (keyboard.Pressed(TIMGE::Key::ESCAPE)) {
        window.SetShouldClose(true);
    }

    // if (keyboard.Pressed(TIMGE::Key::ZERO)) {
    //     mouse.ResetCursor();
    // }
    //
    // if (keyboard.Pressed(TIMGE::Key::ONE)) {
    //     mouse.SetCursor(*cursors[0]);
    // }
    //
    // if (keyboard.Pressed(TIMGE::Key::TWO)) {
    //     mouse.SetCursor(*cursors[1]);
    // }
    //
    // if (keyboard.Pressed(TIMGE::Key::THREE)) {
    //     mouse.SetCursor(*cursors[2]);
    // }

    if (key == TIMGE::Key::D && mods == TIMGE::Modifier::SHIFT) {
        mouse.Disable();
    }

    if (key == TIMGE::Key::H && mods == TIMGE::Modifier::SHIFT) {
        mouse.Hide();
    }

    if (key == TIMGE::Key::C && mods == TIMGE::Modifier::SHIFT) {
        mouse.Capture();
    }

    if (key == TIMGE::Key::R && mods == TIMGE::Modifier::SHIFT) {
        mouse.Restore();
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

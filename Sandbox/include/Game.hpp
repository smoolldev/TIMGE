#ifndef GAME_HPP
#define GAME_HPP

#include <TIMGE/TIMGE.hpp>
#include "Callbacks.hpp"

class Game : public TIMGE::Application
{
    public:
        Game();
        ~Game();
        void BeginFrame();
        void EndFrame();
        void Run();
        void Update();
        void Render();
    private:
        static TIMGE::Application::Info mGameInfo;
        static Game* mInstance;
        static Game* GetInstance();
        void mMainWindow();
        void mLeftWindow();

        friend void ErrorCallback(int errorCode, std::string_view description);
        friend void WindowPosCallback(const TIMGE::V2i32& position);
        friend void WindowSizeCallback(const TIMGE::V2i32& size);
        friend void WindowCloseCallback();
        friend void WindowRefreshCallback();
        friend void WindowFocusCallback(bool focused);
        friend void WindowIconifyCallback(bool iconified);
        friend void WindowMaximizeCallback(bool maximized);
        friend void FramebufferSizeCallback(const TIMGE::V2i32& framebufferSize);
        friend void WindowContentScaleCallback(const TIMGE::V2f& contentScale);
        friend void MouseButtonCallback(TIMGE::Button button, TIMGE::Mouse::Action action, TIMGE::Modifier mods);
        friend void CursorPosCallback(const TIMGE::V2d& cursorPosition);
        friend void CursorEnterCallback(bool entered);
        friend void ScrollCallback(const TIMGE::V2d& cursorScrollOffset);
        friend void KeyCallback(TIMGE::Key key, int scancode, TIMGE::Keyboard::Action action, TIMGE::Modifier mods);
        friend void CharCallback(unsigned int codepoint);
        friend void CharmodsCallback(unsigned int codepoint, int mods);
        friend void DropCallback(int pathCount, const char* paths[]);
        friend void MonitorCallback(int event);
        friend void JoystickCallback(int jid, int event);
};

#endif //GAME_HPP

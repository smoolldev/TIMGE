#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <TIMGE/TIMGE.hpp>
#include "Callbacks.hpp"
#include "TIMGE/Utils/Vector.hpp"

class Game : public TIMGE::Application
{
    public:
        Game();
        ~Game();
        void Run();
        void Update();
        void Render();
    private:
        TIMGE::Monitor& monitor;
        TIMGE::Window& window;
        TIMGE::Mouse& mouse;
        TIMGE::Keyboard& keyboard;
        const std::string_view& mTitle;
        const double& mDeltaTime;
        const TIMGE::V2ui32& mWindowSize;
        const TIMGE::V2i32& mWindowPos;
        const TIMGE::V2ui32& mFramebufferSize;
        const TIMGE::V2ui32& mAspectRatio;
        const TIMGE::V4ui32& mFrameSize;
        const TIMGE::V2f& mContentScale;
        const TIMGE::V2d& mCursorPos;
        const TIMGE::V2d& mScrollOffset;

        const std::vector<TIMGE::Monitor>& mMonitors;

        static TIMGE::Application::Info mGameInfo;
        static Game* mInstance;
        static Game* GetInstance();
        void mWindowSettings();
        void mMonitorSettings();
        void mMouseSettings();
        void mKeybindings();
        void mMenu();

        static constexpr std::array<decltype(&Game::mWindowSettings), 4> windowsXP = {
            &Game::mWindowSettings,
            &Game::mMonitorSettings,
            &Game::mMouseSettings,
            &Game::mKeybindings
        };
 
        void mWindowInfoPosition();
        void mWindowInfoSize();
        void mWindowInfoSizeLimits();
        void mWindowInfoFramebufferSize();
        void mWindowInfoFrameSize();
        void mWindowInfoTitle();
        void mWindowInfoContentScale();
        void mWindowInfoOpacity();
        void mWindowInfoAspectRatio();
        void mWindowAttrMinimize();
        void mWindowAttrMaximize();
        void mWindowAttrRestore();
        void mWindowAttrVisible();
        void mWindowAttrFullscreen();
        void mWindowAttrBorderlessFullscreen();
        void mWindowAttrVSync();
        void mWindowAttrResizeable();
        void mWindowAttrDecorated();
        void mWindowAttrAutoIconify();
        void mWindowAttrFloating();
        void mWindowAttrCenterCursor();
        void mWindowAttrTransparentFramebuffer();
        void mWindowAttrFocusOnShow();
        void mWindowAttrScaleToMonitor();
        void mWindowAttrRequestAttention();

        void mListMonitors();
        void mMonitorInfoPhysicalSize();
        void mMonitorInfoContentScale();
        void mMonitorInfoVirtualPosition();
        void mMonitorInfoWorkarea();
        void mMonitorInfoGamma();

        void mMouseInfoPosition();
        void mMouseInfoScrollOffset();
        void mMouseInfoLeftButton();
        void mMouseInfoRightButton();
        void mMouseInfoDisable();
        void mMouseInfoHide();
        void mMouseInfoCapture();
        void mMouseInfoRestore();
        void mMouseInfoRawMotion();
        void mMouseInfoCursors();

        friend void ErrorCallback(int errorCode, std::string_view description);
        friend void WindowPosCallback(const TIMGE::V2i32& position);
        friend void WindowSizeCallback(const TIMGE::V2ui32& size);
        friend void WindowCloseCallback();
        friend void WindowRefreshCallback();
        friend void WindowFocusCallback(bool focused);
        friend void WindowIconifyCallback(bool iconified);
        friend void WindowMaximizeCallback(bool maximized);
        friend void FramebufferSizeCallback(const TIMGE::V2ui32& framebufferSize);
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

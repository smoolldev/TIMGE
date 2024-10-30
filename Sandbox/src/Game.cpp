#include "Game.hpp"
#include "TIMGE/Window.hpp"

#include <TIMGE/Utils/Vector.hpp>
#include <TIMGE/CallbackDefs.hpp>

#include <imgui.h>

Game* Game::mInstance = nullptr;

TIMGE::Application::Info Game::mGameInfo {
            TIMGE::Window::Info{
                "TIGMA Ballz!",
                TIMGE::V2ui32{720, 480},
                TIMGE::V4ui32{
                    TIMGE::SIZE_LIMITS_DONT_CARE,
                    TIMGE::SIZE_LIMITS_DONT_CARE,
                    TIMGE::SIZE_LIMITS_DONT_CARE,
                    TIMGE::SIZE_LIMITS_DONT_CARE
                },
                TIMGE::V2i32{
                    0, 0 
                },
                TIMGE::V2ui32{
                    TIMGE::ASPECT_RATIO_DONT_CARE,
                    TIMGE::ASPECT_RATIO_DONT_CARE,
                },
                1.0f,
                TIMGE::V2ui32{3, 3},
                671,
            },
            TIMGE::Vector<float, 4>{
                1.0f, 0.63f, 0.1f, 1.0f
            },
            TIMGE::Mouse::Info{
                std::vector<std::filesystem::path>{
                     "resources/nice.png",
                     "resources/empty.png"
                }
            },
            TIMGE::Callback::Callbacks{
                ErrorCallback,
                WindowPosCallback,
                WindowSizeCallback,
                WindowCloseCallback,
                WindowRefreshCallback,
                WindowFocusCallback,
                WindowIconifyCallback,
                WindowMaximizeCallback,
                FramebufferSizeCallback,
                WindowContentScaleCallback,
                MouseButtonCallback,
                CursorPosCallback,
                CursorEnterCallback,
                ScrollCallback,
                KeyCallback,
                CharCallback,
                CharmodsCallback,
                DropCallback,
                MonitorCallback,
                JoystickCallback,
            }
};

Game::Game()
 : Application(Game::mGameInfo),
    mTitle{window.GetTitle()},
    mWindowSize{window.GetSize()},
    mWindowPos{window.GetPosition()},
    mFramebufferSize{window.GetFramebufferSize()},
    mAspectRatio{window.GetAspectRatio()},
    mFrameSize{window.GetFrameSize()},
    mContentScale{window.GetContentScale()}
{
    if (Game::mInstance) {
        throw "Only one instance of Game is allowed!\n";
    }
    mInstance = this;

    window.SetIcon("resources/youtube_logo.png");

    ImGui::SetCurrentContext(GetImGuiContext());
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImFontConfig cfg{};
    cfg.SizePixels = 24;
    io.Fonts->AddFontDefault(&cfg);
    ImGui::StyleColorsDark();
}

Game::~Game()
{}

void Game::Run()
{
    TIMGE::Window& window = GetWindow();

    while (!window.ShouldClose()) {
        Application::BeginFrame();
        {
            Update();
            Render();
        }
        Application::EndFrame();
    }
}

void Game::Update()
{
}

void Game::Render() {
    mMenu();
}

Game* Game::GetInstance() {
    return mInstance;
}

void Game::mWindowSettings()
{
    static bool showWindowSettings = true;
    static ImVec4 new_bg_color;
    ImGui::SetNextWindowPos({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, 0.0f});
    ImGui::SetNextWindowSize({2.0f * (float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("Window Settings", &showWindowSettings, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    |   ImGuiWindowFlags_NoCollapse
    );

    ImGui::Text("Delta Time: %f", deltaTime);

    mWindowInfoTitle();
    mWindowInfoSize();
    mWindowInfoSizeLimits();
    mWindowInfoPosition();
    mWindowInfoFramebufferSize();
    mWindowInfoAspectRatio();
    mWindowInfoFrameSize();
    mWindowInfoContentScale();
    mWindowInfoOpacity();
    mWindowAttrMinimize();
    mWindowAttrMaximize();
    mWindowAttrRestore();
    mWindowAttrVisible();
    mWindowAttrFullscreen();
    mWindowAttrBorderlessFullscreen();
    mWindowAttrVSync();
    mWindowAttrResizeable();
    mWindowAttrDecorated();
    mWindowAttrAutoIconify();
    mWindowAttrFloating();
    mWindowAttrCenterCursor();
    mWindowAttrTransparentFramebuffer();
    mWindowAttrFocusOnShow();
    mWindowAttrScaleToMonitor();
    mWindowAttrRequestAttention();

    if (ImGui::ColorEdit3("", &new_bg_color.x)) {
        SetBackgroundColor(TIMGE::V4f{
            new_bg_color.x,
            new_bg_color.y,
            new_bg_color.z,
            1.0f
        });
    }

    ImGui::End();
}

void Game::mMonitorSettings()
{

}

void Game::mMouseSettings()
{

}

void Game::mKeybindings()
{
    static bool showKeybindings = true;

    ImGui::SetNextWindowPos({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, 0.0f});
    ImGui::SetNextWindowSize({2.0f * (float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("Keybindings", &showKeybindings, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    |   ImGuiWindowFlags_NoCollapse
    );

    ImGui::Text("Exit = Escape");
    ImGui::Text("Minimize = M");
    ImGui::Text("Restore = R");
    ImGui::Text("Maximize = Shift + M");
    ImGui::Text("Show = S");
    ImGui::Text("Hide = Shift + S");
    ImGui::Text("Fullscreen = F11");
    ImGui::Text("Borderless Fullscreen = Control + F11");

    ImGui::End();
}

void Game::mMenu()
{
    static bool showLeftWindow = true;
    static ImVec4 new_bg_color;
    static int windowsXPIndex = 0;

    ImGui::SetNextWindowPos({0.0f, 0.0f});
    ImGui::SetNextWindowSize({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("Menu", &showLeftWindow, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    |   ImGuiWindowFlags_NoTitleBar
    |   ImGuiWindowFlags_NoCollapse
    );

    if (ImGui::Button("Window Settings")) {
        windowsXPIndex = 0;
    }

    if (ImGui::Button("Monitor Settings")) {
        windowsXPIndex = 1;
    }

    if (ImGui::Button("Mouse Settings")) {
        windowsXPIndex = 2;
    }

    if (ImGui::Button("Keybindings")) {
        windowsXPIndex = 3;
    }

    (this->*windowsXP[windowsXPIndex])();

    ImGui::End();
}

void Game::mWindowInfoPosition()
{
    static TIMGE::V2i32 pos_buf = mWindowPos;
    ImGui::Text("Window Position:");
    ImGui::Text("X = %d", mWindowPos[TIMGE::V2i32::X]);
    ImGui::Text("Y = %d", mWindowPos[TIMGE::V2i32::Y]);
    ImGui::InputInt2("##pos_input", &pos_buf[TIMGE::V2i32::X]);
    if (ImGui::IsItemDeactivatedAfterEdit()){
        window.SetPosition(pos_buf);
    } else {
        pos_buf = mWindowPos;
    }
}

void Game::mWindowInfoSize()
{
    static TIMGE::V2ui32 size_buf = mWindowSize;
    ImGui::Text("Window Size:");
    ImGui::Text("Width: %d", mWindowSize[TIMGE::V2i32::WIDTH]);
    ImGui::Text("Height: %d", mWindowSize[TIMGE::V2i32::HEIGHT]);
    //TODO: Sliders
    ImGui::InputInt2("##size_input", reinterpret_cast<int*>(&size_buf[TIMGE::V2i32::X]));

    if (ImGui::IsItemDeactivatedAfterEdit()) {
        window.SetSize(size_buf);
    } else {
        size_buf = mWindowSize;
    }
}

void Game::mWindowInfoSizeLimits()
{
    static TIMGE::V4ui32 sizelims_buf = window.GetSizeLimits();
    ImGui::Text("Window Size Limits:");
    ImGui::Text("Min Width: %d", window.GetSizeLimits()[TIMGE::V4ui32::MIN_WIDTH]);
    ImGui::Text("Min Height: %d", window.GetSizeLimits()[TIMGE::V4ui32::MIN_HEIGHT]);
    ImGui::Text("Max Width: %d", window.GetSizeLimits()[TIMGE::V4ui32::MAX_WIDTH]);
    ImGui::Text("Max Height: %d", window.GetSizeLimits()[TIMGE::V4ui32::MAX_HEIGHT]);
    ImGui::InputInt4("##size_lims", reinterpret_cast<int*>(&sizelims_buf[TIMGE::V4ui32::MIN_WIDTH]));
    
    if (ImGui::IsItemDeactivated()) {
        window.SetSizeLimits(sizelims_buf);
    } else {
        sizelims_buf = window.GetSizeLimits();
    }
}

void Game::mWindowInfoFramebufferSize()
{
    ImGui::Text("Window Framebuffer Size: ");
    ImGui::Text("Width: %d", mFramebufferSize[TIMGE::V2i32::WIDTH]);
    ImGui::Text("Width: %d", mFramebufferSize[TIMGE::V2i32::HEIGHT]);
}

void Game::mWindowInfoFrameSize()
{
    ImGui::Text("Window Frame Size: ");
    ImGui::Text("Top: %d", mFrameSize[TIMGE::V2i32::X]);
    ImGui::Text("Left: %d", mFrameSize[TIMGE::V2i32::Y]);
    ImGui::Text("Bottom: %d", mFrameSize[TIMGE::V2i32::Z]);
    ImGui::Text("Right: %d", mFrameSize[TIMGE::V2i32::W]);
}

void Game::mWindowInfoTitle()
{
    static char title_buf[64]{};
    ImGui::Text("Window Title: %s", mTitle.data());
    ImGui::SetNextItemWidth((float)mWindowSize[TIMGE::V2i32::WIDTH] / 3);
    if (ImGui::InputText("##title_input", title_buf, 63, ImGuiInputTextFlags_EnterReturnsTrue)) {
        window.SetTitle(title_buf);
    }
}

void Game::mWindowInfoContentScale()
{
    ImGui::Text("Window Content Scale: ");
    ImGui::Text("X: %f", mContentScale[TIMGE::V2f::X]);
    ImGui::Text("Y: %f", mContentScale[TIMGE::V2f::Y]);
}

void Game::mWindowInfoOpacity()
{
    static float opacity_buf = window.GetOpacity();
    ImGui::Text("Window Opacity: %.3f", opacity_buf);
    ImGui::SliderFloat("##opacity_input", &opacity_buf, 0.0f, 1.0f);
    if (ImGui::IsItemDeactivated()) {
        window.SetOpacity(opacity_buf);
    }
}

void Game::mWindowInfoAspectRatio()
{
    static TIMGE::V2ui32 ar_buf = window.GetAspectRatio();
    ImGui::Text("Aspect Ratio:");
    ImGui::Text("Numerator: %d", mAspectRatio[TIMGE::V2i32::X]);
    ImGui::Text("Denominator: %d", mAspectRatio[TIMGE::V2i32::Y]);
    ImGui::InputInt2("##ar_input", reinterpret_cast<int*>(&ar_buf[TIMGE::V2i32::X]));
    if (ImGui::IsItemDeactivated()) {
        window.SetAspectRatio(ar_buf);
    }
    else {
        ar_buf = mAspectRatio;
    }
}
void Game::mWindowAttrMinimize()
{
    static bool minimized;
    minimized  = window.GetState(TIMGE::Window::MINIMIZED);

    //TODO: Buttonize
    if (ImGui::Checkbox("Minimize", &minimized)) {
        window.Minimize();
    }
}

void Game::mWindowAttrMaximize()
{
    static bool maximized;
    maximized = window.GetState(TIMGE::Window::MAXIMIZED);
    static bool Switch = maximized;

    if (ImGui::Checkbox("Maximize", &maximized)) {
        if (Switch) {
            window.Restore();
        } else {
            window.Maximize();
        }
        Switch = !Switch;
    }
}

void Game::mWindowAttrRestore()
{
    if (ImGui::Button("Restore")) {
        window.Restore();
    }
}

void Game::mWindowAttrVisible()
{
    static bool visible;
    visible = window.GetState(TIMGE::Window::VISIBLE);

    if (ImGui::Checkbox("Visible", &visible)) {
        window.Hide();
    }
}

void Game::mWindowAttrFullscreen()
{
    static bool fullscreen;
    fullscreen = window.GetState(TIMGE::Window::FULLSCREEN); 

    if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
        window.Fullscreen();
    }
}

void Game::mWindowAttrBorderlessFullscreen()
{
    static bool borderlessFullscreen;
    borderlessFullscreen = window.GetState(TIMGE::Window::BORDERLESS_FULLSCREEN);

    if (ImGui::Checkbox("Borderless Fullscreen", &borderlessFullscreen)) {
        window.BorderlessFullscreen();
    }
}

void Game::mWindowAttrVSync()
{
    static bool vsync;
    vsync = window.GetState(TIMGE::Window::VSYNC);

    if (ImGui::Checkbox("VSync", &vsync)) {
        window.ToggleVSync();
    }
}

void Game::mWindowAttrResizeable()
{
    static bool resizeable;
    resizeable = window.GetState(TIMGE::Window::RESIZABLE);

    if (ImGui::Checkbox("Resizable", &resizeable)) {
        window.ToggleResizable();
    }
}

void Game::mWindowAttrDecorated()
{
    static bool decorated;
    decorated = window.GetState(TIMGE::Window::DECORATED);

    if (ImGui::Checkbox("Decorated", &decorated)) {
        window.ToggleDecorated();
    }
}

void Game::mWindowAttrAutoIconify()
{
    static bool auto_iconify;
    auto_iconify = window.GetState(TIMGE::Window::AUTO_ICONIFY);

    if (ImGui::Checkbox("Auto iconify", &auto_iconify)) {
        window.ToggleAutoIconify();
    }
}

void Game::mWindowAttrFloating()
{
    static bool floating;
    floating = window.GetState(TIMGE::Window::FLOATING);

    if (ImGui::Checkbox("Floating", &floating)) {
        window.ToggleFloating();
    }
}

void Game::mWindowAttrCenterCursor()
{
    static bool center_cursor;
    center_cursor = window.GetState(TIMGE::Window::CENTER_CURSOR);

    if (ImGui::Checkbox("Center", &center_cursor)) {
        window.ToggleCenterCursor();
    }
}

void Game::mWindowAttrTransparentFramebuffer()
{
    static bool transparent;
    transparent = window.GetState(TIMGE::Window::TRANSPARENT_FRAMEBUFFER);

    if (ImGui::Checkbox("Transparent Framebuffer", &transparent)) {
        window.ToggleTransparentFramebuffer();
    }
}

void Game::mWindowAttrFocusOnShow()
{
    static bool focus;
    focus = window.GetState(TIMGE::Window::FOCUS_ON_SHOW);

    if (ImGui::Checkbox("Focus on show", &focus)) {
        window.ToggleFocusOnShow();
    }
}

void Game::mWindowAttrScaleToMonitor()
{
    static bool scale;
    scale = window.GetState(TIMGE::Window::SCALE_TO_MONITOR);

    if (ImGui::Checkbox("Scale to monitor", &scale)) {
        window.ToggleScaleToMonitor();
    }
}

void Game::mWindowAttrRequestAttention()
{

}

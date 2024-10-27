#include "Game.hpp"
#include "TIMGE/Window.hpp"
#include "imgui_internal.h"

#include <TIMGE/Utils/Vector.hpp>
#include <TIMGE/CallbackDefs.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
                    TIMGE::POSITION_DONT_CARE,
                    TIMGE::POSITION_DONT_CARE,
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImFontConfig cfg{};
    cfg.SizePixels = 24;
    io.Fonts->AddFontDefault(&cfg);
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.mGetWindow(), true);
    ImGui_ImplOpenGL3_Init();
}

Game::~Game()
{}

void Game::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    Application::BeginFrame();
}

void Game::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    Application::EndFrame();
}

void Game::Run()
{
    TIMGE::Window& window = GetWindow();

    while (!window.ShouldClose()) {
        BeginFrame();
        {
             Update();
             Render();
        }
        EndFrame();
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
    ImGui::InputInt2("##size_input", reinterpret_cast<int*>(&size_buf[TIMGE::V2i32::X]));

    if (ImGui::IsItemDeactivatedAfterEdit()){
        window.SetSize(size_buf);
    } else {
        size_buf = mWindowSize;
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
    //ImGui::Text("FPS: %d", (int)(deltaTime * 1'000'000.0 / 60.0));
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

    if (ImGui::Checkbox("Minimize", &minimized)) {
        window.Minimize();
    }
}

void Game::mWindowAttrMaximize()
{
    static bool maximized;
    maximized = window.GetState(TIMGE::Window::MAXIMIZED);

    if (ImGui::Checkbox("Maximize", &maximized)) {
        window.Maximize();
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

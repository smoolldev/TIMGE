#include "Game.hpp"

#include <TIMGE/Utils/Vector.hpp>
#include <TIMGE/CallbackDefs.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <chrono>

Game* Game::mInstance = nullptr;

TIMGE::Application::Info Game::mGameInfo {
            TIMGE::Window::Info{
                "TIGMA Ballz!",
                720,
                480,
                0,
                0,
                0,
                0,
                3,
                3,
                671,
                false,
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

void Game::Render()
{
    mLeftWindow();
    mMainWindow();
}

Game* Game::GetInstance() {
    return mInstance;
}

void Game::mMainWindow()
{
    static bool showMainWindow = true;
    static ImVec4 new_bg_color;
    ImGui::SetNextWindowPos({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, 0.0f});
    ImGui::SetNextWindowSize({2.0f * (float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("Window settings", &showMainWindow, 
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
    mWindowInfoFullscreen();
    mWindowAttrMinimize();
    mWindowAttrMaximize();
    mWindowAttrRestore();
    mWindowAttrShow();
    mWindowAttrHide();
    mWindowAttrFocus();
    mWindowAttrRequestAttention();
    mWindowAttrFullscreen();
    mWindowAttrBorderlessFullscreen();

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

void Game::mLeftWindow()
{
    static bool showLeftWindow = true;
    static ImVec4 new_bg_color;

    ImGui::SetNextWindowPos({0.0f, 0.0f});
    ImGui::SetNextWindowSize({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("LeftWindow", &showLeftWindow, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    |   ImGuiWindowFlags_NoTitleBar
    |   ImGuiWindowFlags_NoCollapse
    );


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
    static TIMGE::V2i32 size_buf = mWindowSize;
    ImGui::Text("Window Size:");
    ImGui::Text("Width: %d", mWindowSize[TIMGE::V2i32::WIDTH]);
    ImGui::Text("Height: %d", mWindowSize[TIMGE::V2i32::HEIGHT]);
    ImGui::InputInt2("##size_input", &size_buf[TIMGE::V2i32::X]);
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

void Game::mWindowInfoFullscreen()
{
    static bool set_fscr = window.GetFullscreen();
    if (ImGui::Checkbox("Fullscreen", &set_fscr)) {
        window.Fullscreen();
    }
    static bool set_bjfscr = window.GetFullscreen();
    if (ImGui::Checkbox("Blowjob Fullscreen", &set_bjfscr)) {
        window.BorderlessFullscreen();
    }
}

void Game::mWindowInfoAspectRatio()
{
    static TIMGE::V2i32 ar_buf = window.GetAspectRatio();
    ImGui::Text("Aspect Ratio:");
    ImGui::Text("Numerator: %d", mAspectRatio[TIMGE::V2i32::X]);
    ImGui::Text("Denominator: %d", mAspectRatio[TIMGE::V2i32::Y]);
    ImGui::InputInt2("##ar_input", &ar_buf[TIMGE::V2i32::X]);
    if (ImGui::IsItemDeactivated()) {
        window.SetAspectRatio(ar_buf);
    }
    else {
        ar_buf = mAspectRatio;
    }
}
void Game::mWindowAttrMinimize()
{

}

void Game::mWindowAttrMaximize()
{

}

void Game::mWindowAttrRestore()
{

}

void Game::mWindowAttrShow()
{

}

void Game::mWindowAttrHide()
{

}

void Game::mWindowAttrFocus()
{

}

void Game::mWindowAttrRequestAttention()
{

}

void Game::mWindowAttrFullscreen()
{

}

void Game::mWindowAttrBorderlessFullscreen()
{

}

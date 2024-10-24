#include "Game.hpp"

#include <TIMGE/Utils/Vector.hpp>
#include <TIMGE/CallbackDefs.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
 : Application(Game::mGameInfo)
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
    static const auto& window_size = window.GetSize();
    static ImVec4 new_bg_color;
    ImGui::SetNextWindowPos({(float)window_size[TIMGE::V2i32::WIDTH] / 3.0f, 0.0f});
    ImGui::SetNextWindowSize({2.0f * (float)window_size[TIMGE::V2i32::WIDTH] / 3.0f, (float)window_size[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("MainWindow", &showMainWindow, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    |   ImGuiWindowFlags_NoTitleBar
    |   ImGuiWindowFlags_NoCollapse
    );
    
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
    static const auto& window_size = window.GetSize();
    static const auto& window_pos = window.GetPosition();
    static ImVec4 new_bg_color;
    static const auto& title = window.GetTitle();
    static char title_buf[64];
    static TIMGE::V2i32 size_buf{window_size};
    static TIMGE::V2i32 pos_buf{window_pos};
    static bool set_fscr = window.GetFullscreen();

    ImGui::SetNextWindowPos({0.0f, 0.0f});
    ImGui::SetNextWindowSize({(float)window_size[TIMGE::V2i32::WIDTH] / 3, (float)window_size[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("LeftWindow", &showLeftWindow, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    |   ImGuiWindowFlags_NoTitleBar
    |   ImGuiWindowFlags_NoCollapse
    );

    ImGui::Text("FPS: %d", (int)(deltaTime * 1'000'000.0 / 60.0));
    ImGui::Text("Window Title: %s", title.data());
    ImGui::SetNextItemWidth((float)window_size[TIMGE::V2i32::WIDTH] / 3);
    if (ImGui::InputText("##title_input", title_buf, 63, ImGuiInputTextFlags_EnterReturnsTrue)) {
        window.SetTitle(title_buf);
    }

    ImGui::Text("Window Size:");
    ImGui::Text("Width: %d", window_size[TIMGE::V2i32::WIDTH]);
    ImGui::Text("Height: %d", window_size[TIMGE::V2i32::HEIGHT]);
    ImGui::InputInt2("##size_input", &size_buf[TIMGE::V2i32::X]);
    if (ImGui::IsItemDeactivatedAfterEdit()){
        window.SetSize(size_buf);
    } else {
        size_buf = window_size;
    }

    ImGui::Text("Window Position:");
    ImGui::Text("X = %d", window_pos[TIMGE::V2i32::X]);
    ImGui::Text("Y = %d", window_pos[TIMGE::V2i32::Y]);
    ImGui::InputInt2("##pos_input", &pos_buf[TIMGE::V2i32::X]);
    if (ImGui::IsItemDeactivatedAfterEdit()){
        window.SetPosition(pos_buf);
    } else {
        pos_buf = window_pos;
    }
    
    ImGui::End();
}

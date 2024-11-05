#include "Game.hpp"

#include <imgui.h>
#include <iostream>
#include <vector>

#include <TIMGE/TIMGE.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>

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
                671 | TIMGE::Window::TRANSPARENT_FRAMEBUFFER,
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
    monitor{GetMonitor()},
    window{Application::GetWindow()},
    mouse{Application::GetMouse()},
    keyboard{Application::GetKeyboard()},
    mTitle{window.GetTitle()},
    mDeltaTime{Application::GetDeltaTime()},
    mWindowSize{window.GetSize()},
    mWindowPos{window.GetPosition()},
    mFramebufferSize{window.GetFramebufferSize()},
    mAspectRatio{window.GetAspectRatio()},
    mFrameSize{window.GetFrameSize()},
    mContentScale{window.GetContentScale()},
    mMonitors{GetMonitor().GetMonitors()},
    mCursorPos{mouse.GetPosition()},
    mScrollOffset{mouse.GetOffset()}
{
    if (Game::mInstance) {
        throw "Only one instance of Game is allowed!\n";
    }
    mInstance = this;

    window.SetIcon("resources/youtube_logo.png");

    ImGui::SetCurrentContext(GetImGuiContext());
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
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

    /*GLuint VBO, VAO, IBO;*/

    /*float vertices[] = */
    /*{*/
    /*    0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,*/
    /*    -0.25f, -0.75f, 0.0f, 0.0f, 1.0f, 0.0f,*/
    /*    0.25f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f,*/
    /*};*/

    // there's an error when compiling the code, something about a brace initializer list or something i don't know I gotta go to school or im going to be late.
    std::vector<TIMGE::ColoredVertex> vertices
    {
        { 0.0f,   0.5f,  0.0f, 1.0f, 0.0f, 0.0f },
        {-0.25f, -0.75f, 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.25f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f }
    };

    /*std::vector<float> vertices*/
    /*{*/
    /*     0.0f,   0.5f,  0.0f, 1.0f, 0.0f, 0.0f,*/
    /*    -0.25f, -0.75f, 0.0f, 0.0f, 1.0f, 0.0f,*/
    /*     0.25f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f*/
    /*};*/

    const char* vertex_shader = 
    R"(
        #version 330 core

        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aCol;

        out vec3 Col;
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
            Col = aCol;
        }
    )";

    const char* fragment_shader = 
    R"(
        #version 330 core

        in vec3 Col;
        out vec4 FragColor;

        void main() {
            FragColor = vec4(Col, 1.0);
        }
    )";

    unsigned int VAO;

    /*TIMGE::VertexArray VAO(1);*/
    /*TIMGE::Buffer VBO(1, TIMGE::Buffer::VERTEX, TIMGE::Buffer::STATIC_DRAW);*/
    /**/
    /*VAO.Generate();*/
    /*VAO.Bind();*/
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //TIMGE::VertexBuffer vbo(TIMGE::Buffer::STATIC_DRAW);
    //vbo.Bind();
    //vbo.Data(vertices);

    /**/
    /*VBO.Generate();*/
    /*VBO.Bind(vertices, sizeof(vertices));*/
    /**/
    /*VBO.InterpretVertexBufferData(0, 3, 6 * sizeof(float), TIMGE::Buffer::DataType::FLOAT, false, vertices, 0);*/
    /*VBO.InterpretVertexBufferData(1, 3, 6 * sizeof(float), TIMGE::Buffer::DataType::FLOAT, false, vertices, 3 * sizeof(float));*/

    //VBO.Unbind();

    //VAO.Unbind();

    TIMGE::VertexBuffer vbo;
    //glGenBuffers(1, &VBO);
    vbo.Bind();
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    vbo.Data(vertices);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TIMGE::ColoredVertex), vertices.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    GLuint vs, fs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    int vs_success;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_success);
    if (!vs_success) 
    {
        char info_log[512];
        glGetShaderInfoLog(vs, 512, nullptr, info_log);
        std::cout << info_log << '\n';
    }

    int fs_success;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_success);
    if (!fs_success) 
    {
        char info_log[512];
        glGetShaderInfoLog(vs, 512, nullptr, info_log);
        std::cout << info_log << '\n';
    }

    GLuint shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);

    int shader_success;
    glGetProgramiv(shader, GL_LINK_STATUS, &shader_success);
    if (!shader_success)
    {
        char info_log[512];
        glGetProgramInfoLog(shader, 512, nullptr, info_log);
    }

    glUseProgram(shader);
    glViewport(0, 0, 720, 480);

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
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
    );

    ImGui::Text("Delta Time: %f", mDeltaTime);

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

    if (ImGui::ColorEdit4("", &new_bg_color.x)) {
        SetBackgroundColor(TIMGE::V4f{
            new_bg_color.x,
            new_bg_color.y,
            new_bg_color.z,
            new_bg_color.w
        });
    }

    ImGui::End();
}

void Game::mMonitorSettings()
{
    static bool showMonitorSettings = true;

    ImGui::SetNextWindowPos({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, 0.0f});
    ImGui::SetNextWindowSize({2.0f * (float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("Keybindings", &showMonitorSettings, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    );

    mListMonitors();
    mMonitorInfoPhysicalSize();
    mMonitorInfoContentScale();
    mMonitorInfoVirtualPosition();
    mMonitorInfoWorkarea();
    mMonitorInfoGamma();

    ImGui::End();
}

void Game::mMouseSettings()
{
    static bool showMouseSettings = true;

    ImGui::SetNextWindowPos({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, 0.0f});
    ImGui::SetNextWindowSize({2.0f * (float)mWindowSize[TIMGE::V2i32::WIDTH] / 3.0f, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("Mouse", &showMouseSettings, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    );

    mMouseInfoPosition();
    mMouseInfoScrollOffset();
    mMouseInfoLeftButton();
    mMouseInfoRightButton();
    mMouseInfoDisable();
    mMouseInfoHide();
    mMouseInfoCapture();
    mMouseInfoRestore();
    mMouseInfoRawMotion();
    mMouseInfoCursors();

    ImGui::End();
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
    );

    ImGui::Text("Exit = Escape");
    ImGui::Text("Minimize = M");
    ImGui::Text("Maximize = Shift + M");
    ImGui::Text("Window Restore = R");
    ImGui::Text("Mouse Restore = Control + R");
    ImGui::Text("Raw Mouse Motion = Shift + R");
    ImGui::Text("Show = S");
    ImGui::Text("Hide = Shift + S");
    ImGui::Text("Fullscreen = F11");
    ImGui::Text("Borderless Fullscreen = Control + F11");
    ImGui::Text("Center Cursor = L");
    ImGui::Text("Hide cursor = H");
    ImGui::Text("Capture cursor = C");
    ImGui::Text("Disable cursor = D");

    ImGui::End();
}

void Game::mMenu()
{
    static bool showLeftWindow = true;
    static ImVec4 new_bg_color;
    static int windowsXPIndex = 1;

    ImGui::SetNextWindowPos({0.0f, 0.0f});
    ImGui::SetNextWindowSize({(float)mWindowSize[TIMGE::V2i32::WIDTH] / 3, (float)mWindowSize[TIMGE::V2i32::HEIGHT]});
    ImGui::Begin("Menu", &showLeftWindow, 
        ImGuiWindowFlags_NoNav
    |   ImGuiWindowFlags_NoMove
    |   ImGuiWindowFlags_NoResize
    |   ImGuiWindowFlags_NoTitleBar
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
    ImGui::SliderFloat("##opacity_input", &opacity_buf, 0.1f, 1.0f);
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

void Game::mListMonitors()
{
    ImGui::Text("# of monitors: %zu", mMonitors.size());

    ImGui::Text("\nList of monitors:");
    for (int i = 0; i < mMonitors.size(); i++) {
        ImGui::Text("\t");
        ImGui::SameLine();
        ImGui::Button(std::format("{}: {}", i, mMonitors[i].GetName().data()).c_str());

        if (ImGui::IsItemDeactivated()) {
            SetMonitor(mMonitors[i]);
        }
    }
}

void Game::mMonitorInfoPhysicalSize()
{
    const TIMGE::V2ui32& physicalSize = monitor.GetPhysicalSize();

    ImGui::Text("Monitor physical size:");
    ImGui::Text("\tWidth: %u", physicalSize[TIMGE::V2ui32::WIDTH]);
    ImGui::Text("\tHeight: %u", physicalSize[TIMGE::V2ui32::HEIGHT]);
}

void Game::mMonitorInfoContentScale()
{
    const TIMGE::V2f& contentScale = monitor.GetContentScale();

    ImGui::Text("Monitor content scale:");
    ImGui::Text("\tX: %f", contentScale[TIMGE::V2f::X]);
    ImGui::Text("\tY: %f", contentScale[TIMGE::V2f::Y]);
}

void Game::mMonitorInfoVirtualPosition()
{
    const TIMGE::V2i32& virtualPosition = monitor.GetVirtualPosition();

    ImGui::Text("Monitor virtual position:");
    ImGui::Text("\tX: %d", virtualPosition[TIMGE::V2i32::X]);
    ImGui::Text("\tY: %d", virtualPosition[TIMGE::V2i32::Y]);
}

void Game::mMonitorInfoWorkarea()
{
    const TIMGE::V2i32& workareaPosition = monitor.GetWorkareaPosition();
    const TIMGE::V2ui32& workareaSize = monitor.GetWorkareaSize();

    ImGui::Text("Monitor workarea:");
    ImGui::Text("\tX: %d", workareaPosition[TIMGE::V2i32::X]);
    ImGui::Text("\tY: %d", workareaPosition[TIMGE::V2i32::Y]);
    ImGui::Text("\tWidth: %d", workareaSize[TIMGE::V2ui32::WIDTH]);
    ImGui::Text("\tHeight: %d", workareaSize[TIMGE::V2ui32::HEIGHT]);
}

void Game::mMonitorInfoGamma()
{
    static float gamma = monitor.GetGamma();

    ImGui::Text("Monitor gamma: %.3f", gamma);
    ImGui::InputFloat("##gamma_input", &gamma);
    if (ImGui::IsItemDeactivated()) {
        monitor.SetGamma(gamma);
    } else {
        gamma = monitor.GetGamma();
    }
}

void Game::mMouseInfoPosition()
{
    ImGui::Text("Cursor Position:");
    ImGui::Text("\tX: %f", mCursorPos[TIMGE::V2d::X]);
    ImGui::Text("\tX: %f", mCursorPos[TIMGE::V2d::Y]);
}

void Game::mMouseInfoScrollOffset()
{
    ImGui::Text("Scroll Offset:");
    ImGui::Text("\tOffset X: %f", mScrollOffset[TIMGE::V2d::X]);
    ImGui::Text("\tOffset Y: %f", mScrollOffset[TIMGE::V2d::Y]);
}

void Game::mMouseInfoLeftButton()
{
    ImGui::Text("Mouse Button Left:");
    ImGui::Text("\tState: %s", mouse.Pressed(TIMGE::Button::LEFT) ? "Pressed" : "Released");
}

void Game::mMouseInfoRightButton()
{
    ImGui::Text("Mouse Button Right:");
    ImGui::Text("\tState: %s", mouse.Pressed(TIMGE::Button::RIGHT) ? "Pressed" : "Released");
}

void Game::mMouseInfoDisable()
{
    static bool disabled;
    disabled = mouse.GetState(TIMGE::Mouse::DISABLED);
    if (ImGui::Checkbox("Disabled", &disabled)) {
        mouse.Disable();
    }
}

void Game::mMouseInfoHide()
{
    static bool hidden;
    hidden = mouse.GetState(TIMGE::Mouse::HIDDEN);
    if (ImGui::Checkbox("Hidden", &hidden)) {
        mouse.Hide();
    }
}

void Game::mMouseInfoCapture()
{
    static bool captured;
    captured = mouse.GetState(TIMGE::Mouse::CAPTURED);
    if (ImGui::Checkbox("Captured", &captured)) {
        mouse.Capture();
    }
}

void Game::mMouseInfoRestore()
{
    if (ImGui::Button("Restore")) {
        mouse.Restore();
    }
}

void Game::mMouseInfoRawMotion()
{
    if (!mouse.IsRawMouseMotionSupported()) {
        return;
    }

    static bool raw_motion;
    raw_motion = mouse.GetState(TIMGE::Mouse::RAW_MOTION);
    if (ImGui::Checkbox("Raw Motion", &raw_motion)) {
        mouse.RawMotion();
    }
}

void Game::mMouseInfoCursors()
{
    static  std::vector<TIMGE::Cursor*> cursors;
    cursors = mouse.GetCursors();

    for (int i = 0; i < cursors.size(); i++)
    {
        if (ImGui::Button(std::format("Set {}", i).c_str())) {
            mouse.SetCursor(*cursors[i]);
        }
        ImGui::SameLine();
        if (ImGui::Button(std::format("Delete ##{}", i).c_str())) {
            mouse.DeleteCursor(*cursors[i]);
        }
    }
    if (ImGui::Button("Reset cursor")) {
        mouse.ResetCursor();
    }
}

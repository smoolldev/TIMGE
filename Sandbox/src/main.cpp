#include "TIMGE/Utils/Vector.hpp"
#include <TIMGE/CallbackDefs.hpp>
#include <TIMGE/TIMGE.hpp>

#include <cstdio>
#include <format>
#include <cstdlib>
#include <GLFW/glfw3.h>

using namespace TIMGE;

class Game : public Application
{
    public:
    Game();
    ~Game() {}
    void Run();
    void Update();
    void Render();

    friend void CursorPosCallback(double xPos, double yPos);
    friend void KeyCallback(Key key, int scancode, Action action, Modifier mods);

    private:
        static Game* mInstance;
        static Game* GetInstance();
};

void CursorPosCallback(double xPos, double yPos);
void KeyCallback(Key key, int scancode, Action action, Modifier mods);

Window::Info win_info = 
{
    "Callbacks", /*mTitle*/
    1000, /*mWidth*/
    500, /*mHeight*/
    200, /*mMinWidth*/
    100, /*mMinHeight*/
    0, /*mMaxWidth*/
    0, /*mMaxHeight*/
    3, /*mOpenGLVersionMajor*/
    3, /*mOpenGLVersionMinor*/
    671, /*mFlags*/
    "/home/marcel/Dev/C++/TIMGE/Sandbox/resources/youtube_logo.png", /*mIconPath*/
    false, /*mIsFullscreen*/
};

Vector<float, 4> color = {1.0f, 0.63f, 0.1f, 1.0f};

Callback::Callbacks callbacks{};

Game* Game::mInstance = nullptr;

Game::Game()
 : Application({win_info, {}, color, callbacks})
{
    if (Game::mInstance) {
        throw "Only one instance of Game is allowed!\n";
    }
    mInstance = this;
}

Game* Game::GetInstance() {
    return mInstance;
}
void Game::Run()
{
    Window& window = GetWindow();

    while (!window.ShouldClose()) {
         Application::BeginFrame();
         {
             Update();
             V2i32 size = window.GetSize();
             printf("width = %d, height = %d\r", size[V2i32::WIDTH], size[V2i32::HEIGHT]);
             Render();
         }
         Application::EndFrame();
    }
}

void Game::Update()
{
    // if (glfwGetKey(GetWindow().GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    //     glfwSetWindowShouldClose(GetWindow().GetWindow(), 1);
    // } else if (glfwGetKey(GetWindow().GetWindow(), GLFW_KEY_F11) == GLFW_PRESS)
    // {
    //     static bool isMaximized = false;
    //     if (!isMaximized) {
    //     Application::GetWindow().Maximize();
    //     } else {
    //         GetWindow().Restore();
    //     }
    //
    //     isMaximized = !isMaximized;
    // } else if (glfwGetKey(GetWindow().mWindow, GLFW_KEY_F8) == GLFW_PRESS)
    // {
    //     static bool isHidden = false;
    //     if (!isHidden) {
    //         GetWindow().Hide();
    //     } else {
    //         GetWindow().Show();
    //     }
    //
    //     isHidden = !isHidden;
    // } else if (glfwGetKey(GetWindow().mWindow, GLFW_KEY_F12) == GLFW_PRESS) {
    //     GetWindow().Fullscreen();
    // }
}

void Game::Render()
{

}

int main()
{
    callbacks.mCursorPos = CursorPosCallback;
    callbacks.mKey = KeyCallback;
    Game game;
    game.Run();
}

void CursorPosCallback(double xPos, double yPos)
{
    Game::GetInstance()->GetWindow().SetTitle(std::format("x = {}, y = {}", xPos, yPos));
}

void KeyCallback(Key key, int scancode, Action action, Modifier mods)
{
    Game* game = Game::GetInstance();
    Window& window = game->GetWindow();
    Keyboard& keyboard = game->GetKeyboard();

    if (keyboard.Pressed(TIMGE::Key::ESCAPE)) {
        window.SetShouldClose(true);
    }
}

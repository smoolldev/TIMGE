#include <TIMGE/TIMGE.hpp>

#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace TIMGE;

class Game : public Application
{
    public:
    Game() : Application("TIMGESandbox", 720, 480) {}
    ~Game() {}
    void Run();
    void Update();
    void Render();
};

void Game::Run()
{
    //GetWindow().mInfo.mIconPath = "./resources/youtube_logo.png";
    //GetWindow().SetIcon("resource/youtube_logo.png");
    //GetWindow().SetIcon("Default");
    //GetWindow().SetIcon();
    //system("pwd");
    while (!Application::WindowShouldClose()) {
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
    //GetWindow().SetAspectRatio(21, 9);
    if (glfwGetKey(GetWindow().GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(GetWindow().GetWindow(), 1);
    } else if (glfwGetKey(GetWindow().GetWindow(), GLFW_KEY_F11) == GLFW_PRESS)
    {
        static bool isMaximized = false;
        if (!isMaximized) {
        Application::GetWindow().Maximize();
        } else {
            GetWindow().Restore();
        }

        isMaximized = !isMaximized;
    } else if (glfwGetKey(GetWindow().mWindow, GLFW_KEY_F8) == GLFW_PRESS)
    {
        static bool isHidden = false;
        if (!isHidden) {
            GetWindow().Hide();
        } else {
            GetWindow().Show();
        }

        isHidden = !isHidden;
    } else if (glfwGetKey(GetWindow().mWindow, GLFW_KEY_F12) == GLFW_PRESS) {
        GetWindow().Fullscreen();
    }
}

void Game::Render()
{

}

int main()
{
    Game game;
    game.Run();
}

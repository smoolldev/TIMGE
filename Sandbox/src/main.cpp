#include <TIMGE/TIMGE.hpp>

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
    //mWindow.mInfo.mIconPath = "./resources/youtube_logo.png";
    mWindow.SetIcon("/home/smoolldev/SmoollDev/smoolldev/Development/CPP/TIMGE/Sandbox/build/linux_x64-Debug/resources/youtube_logo.png");
    //mWindow.SetIcon("Default");
    //mWindow.SetIcon();
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
 //    if (glfwGetKey(mWindow.mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	// glfwSetWindowShouldClose(mWindow.mWindow, 1);
 //    }
}

void Game::Render()
{

}

int main()
{
    Game game;
    game.Run();
}

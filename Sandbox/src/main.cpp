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
    //mWindow.mInfo.mIconPath = "./resources/youtube_logo.png";
<<<<<<< HEAD
=======
    mWindow.SetIcon("./resources/youtube_logo.png");
>>>>>>> 95619f16ea688a9160a4295eafed4d995e0fc761
    //mWindow.SetIcon("Default");
    //mWindow.SetIcon();
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
    if (glfwGetKey(mWindow.mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	glfwSetWindowShouldClose(mWindow.mWindow, 1);
    }
    else if (glfwGetKey(mWindow.mWindow, GLFW_KEY_F11) == GLFW_PRESS) {
	static bool isMaximized = false;
	if (!isMaximized) {
	    mWindow.Maximize();
	} else {
	    mWindow.Restore();
	}

	isMaximized = !isMaximized;
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

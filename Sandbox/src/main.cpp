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
    mWindow.SetIcon("resource/youtube_logo.png");
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
    //mWindow.SetAspectRatio(21, 9);
    if (glfwGetKey(mWindow.mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	    glfwSetWindowShouldClose(mWindow.mWindow, 1);
    } else if (glfwGetKey(mWindow.mWindow, GLFW_KEY_F11) == GLFW_PRESS)
    {
	    static bool isMaximized = false;
	    if (!isMaximized) {
	        mWindow.Maximize();
	    } else {
	        mWindow.Restore();
	    }

	    isMaximized = !isMaximized;
    } else if (glfwGetKey(mWindow.mWindow, GLFW_KEY_F8) == GLFW_PRESS)
    {
        static bool isHidden = false;
        if (!isHidden) {
            mWindow.Hide();
        } else {
            mWindow.Show();
        }

        isHidden = !isHidden;
    } else if (glfwGetKey(mWindow.mWindow, GLFW_KEY_F12) == GLFW_PRESS) {
        mWindow.Fullscreen();
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

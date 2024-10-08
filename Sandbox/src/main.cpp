#include <TIMGE/TIMGE.hpp>
#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game : public TIMGE::Application
{
    public:
        Game(std::string_view title, uint32_t width, uint32_t height)
            : TIMGE::Application(title, width, height)
        {
            
        }
        ~Game() { };

        void Run();

        void Update() { }

        void Render() { }
};

void Game::Run()
{
    while (!glfwWindowShouldClose(mWindow.mWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 0, 1);
        glfwSwapBuffers(mWindow.mWindow);
        glfwPollEvents();
    }
}

int main(int argc, char **argv)
{
    try {
        Game game("title", 1280, 720);

        game.Run();
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }

    /*if (!game)*/
    /*{ exit(-1); }*/

    return 0;
}

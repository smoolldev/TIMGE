#include <TIMGE/TIMGE.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace TIMGE;

class Game : public Application
{
    public:
    Game() : Application("TIMGE", 720, 480) {}
    ~Game() {}
    void Run() {}
    void Update() {}
    void Render() {}
};

int main()
{
    Game game;
    
    while (!glfwWindowShouldClose(game.mWindow.mWindow)) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.1f, .1f, 1.0f, 1.0f);

	glfwSwapBuffers(game.mWindow.mWindow);
	glfwPollEvents();
    }
}

#include "TIMGE/Application.hpp"
#include "TIMGE/Keyboard.hpp"
#include "TIMGE/Mouse.hpp"
#include "TIMGE/Utils/Vector.hpp"
#include <TIMGE/CallbackDefs.hpp>
#include <TIMGE/TIMGE.hpp>

#include <GLFW/glfw3.h>

#include <stdexcept>
#include <cstdio>
#include <iostream>

using namespace TIMGE;

class Game : public Application
{
    public:
    Game();
    ~Game() {}
    void Run();
    void Update();
    void Render();

    friend void CursorPosCallback(const V2d& cursorPosition);
    friend void KeyCallback(Key key, int scancode, TIMGE::Keyboard::Action action, Modifier mods);
    friend void DropCallback(int pathCount, const char* path[]);

    private:
        static Game* mInstance;
        static Game* GetInstance();
};

void CursorPosCallback(const V2d& cursorPosition);
void KeyCallback(Key key, int scancode, TIMGE::Keyboard::Action action, Modifier mods);
void DropCallback(int pathCount, const char* path[]);

Vector<float, 4> color = {1.0f, 0.63f, 0.1f, 1.0f};

Callback::Callbacks callbacks{};

Game* Game::mInstance = nullptr;

Game::Game()
 : Application(
         {
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
                {},//"resources/youtube_logo.png", /*mIconPath*/
                false, /*mIsFullscreen*/
            },
            {
                1.0f, 0.63f, 0.1f, 1.0f
            },
            {
                // {
                //     "resources/nice.png",
                //     "resources/empty.png"
                // }
            },
            callbacks
         })
{
    if (Game::mInstance) {
        throw "Only one instance of Game is allowed!\n";
    }
    mInstance = this;

    Mouse& mouse = GetMouse();

    // mouse.AddCursor("resources/cursor.png");
    // mouse.AddCursor("resources/cursor (1).png");
    // mouse.AddCursor(TIMGE::StandardCursor::IBEAM_CURSOR);
    // mouse.AddCursor(TIMGE::StandardCursor::POINTING_HAND_CURSOR);
    //
    // auto cursors = mouse.GetCursors();
    //
    // mouse.DeleteCursor(*cursors[1]);
    //
    // cursors = mouse.GetCursors();
    //
    // mouse.DeleteCursor(*cursors[1]);
    //
    // mouse.SetCursor(*cursors[1]);
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
    callbacks.mDrop = DropCallback;

    try {
        Game game;
        game.Run();
    } catch (const std::out_of_range& oor) {
        std::cerr << "Something went wront: " << oor.what() << "!\n";
    } catch (const char* e) {
        std::cerr << "Something went wront: " << e << "!\n";
    }
}

void CursorPosCallback(const V2d& cursorPosition)
{
}

void KeyCallback(Key key, int scancode, TIMGE::Keyboard::Action action, Modifier mods)
{
    Game* game = Game::GetInstance();
    Window& window = game->GetWindow();
    Keyboard& keyboard = game->GetKeyboard();
    Mouse& mouse = game->GetMouse();
    auto cursors = mouse.GetCursors();

    if (keyboard.Pressed(TIMGE::Key::ESCAPE)) {
        window.SetShouldClose(true);
    }

    // if (keyboard.Pressed(TIMGE::Key::ZERO)) {
    //     mouse.ResetCursor();
    // }
    //
    // if (keyboard.Pressed(TIMGE::Key::ONE)) {
    //     mouse.SetCursor(*cursors[0]);
    // }
    //
    // if (keyboard.Pressed(TIMGE::Key::TWO)) {
    //     mouse.SetCursor(*cursors[1]);
    // }
    //
    // if (keyboard.Pressed(TIMGE::Key::THREE)) {
    //     mouse.SetCursor(*cursors[2]);
    // }

    if (key == TIMGE::Key::D && mods == TIMGE::Modifier::SHIFT) {
        mouse.Disable();
    }

    if (key == TIMGE::Key::H && mods == TIMGE::Modifier::SHIFT) {
        mouse.Hide();
    }

    if (key == TIMGE::Key::C && mods == TIMGE::Modifier::SHIFT) {
        mouse.Capture();
    }

    if (key == TIMGE::Key::R && mods == TIMGE::Modifier::SHIFT) {
        mouse.Restore();
    }
}

void DropCallback(int pathCount, const char* path[]) {
    printf("Paths: %d\n\n", pathCount);

    for (int i = 0; i < pathCount; i++) {
        printf("Path: %s\n", path[i]);
    }
}

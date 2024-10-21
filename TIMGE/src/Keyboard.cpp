#include "TIMGE/Keyboard.hpp"
#include "TIMGE/Window.hpp"

#include <GLFW/glfw3.h>

namespace TIMGE
{
    Keyboard::Keyboard(Window& window)
     : mWindow{window}
    {}

    bool Keyboard::Pressed(Key key) const {
        return glfwGetKey(mWindow.mGetWindow(), static_cast<int>(key)) == GLFW_PRESS;
    }

    bool Keyboard::Pressed(Modifier modifier) const {
        return glfwGetKey(mWindow.mGetWindow(), static_cast<int>(modifier)) == GLFW_PRESS;
    }

    bool Keyboard::Released(Key key) const {
        return glfwGetKey(mWindow.mGetWindow(), static_cast<int>(key)) == GLFW_RELEASE;
    }

    bool Keyboard::Released(Modifier modifier) const {
        return glfwGetKey(mWindow.mGetWindow(), static_cast<int>(modifier)) == GLFW_RELEASE;
    }

    bool Keyboard::Repeat(Key key) const {
        return glfwGetKey(mWindow.mGetWindow(), static_cast<int>(key)) == GLFW_REPEAT;
    }

    bool Keyboard::Repeat(Modifier modifier) const {
        return glfwGetKey(mWindow.mGetWindow(), static_cast<int>(modifier)) == GLFW_REPEAT;
    }

    int Keyboard::GetScancode(Key key) const {
        return glfwGetKeyScancode(static_cast<int>(key));
    }
}

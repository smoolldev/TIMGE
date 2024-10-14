#include "TIMGE/Keyboard.hpp"
#include "GLFW/glfw3.h"
#include "TIMGE/Window.hpp"

namespace TIMGE
{
    Keyboard::Keyboard(Window& window)
     : mWindow{window}
    {}

    bool Keyboard::Pressed(const Key& key) const {
        return glfwGetKey(mWindow.GetWindow(), static_cast<int>(key)) == GLFW_PRESS;
    }

    bool Keyboard::Pressed(Modifier modifier) const {
        return glfwGetKey(mWindow.GetWindow(), static_cast<int>(modifier)) == GLFW_PRESS;
    }

    bool Keyboard::Released(const Key& key) const {
        return glfwGetKey(mWindow.GetWindow(), static_cast<int>(key)) == GLFW_RELEASE;
    }

    bool Keyboard::Released(Modifier modifier) const {
        return glfwGetKey(mWindow.GetWindow(), static_cast<int>(modifier)) == GLFW_RELEASE;
    }

    bool Keyboard::Repeat(const Key& key) const {
        return glfwGetKey(mWindow.GetWindow(), static_cast<int>(key)) == GLFW_REPEAT;
    }

    bool Keyboard::Repeat(Modifier modifier) const {
        return glfwGetKey(mWindow.GetWindow(), static_cast<int>(modifier)) == GLFW_REPEAT;
    }

    int Keyboard::GetScancode(const Key& key) const {
        return glfwGetKeyScancode(static_cast<int>(key));
    }
}

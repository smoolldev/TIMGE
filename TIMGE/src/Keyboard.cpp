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

    bool Keyboard::Released(const Key& key) const {
        return glfwGetKey(mWindow.GetWindow(), static_cast<int>(key)) == GLFW_RELEASE;
    }
}

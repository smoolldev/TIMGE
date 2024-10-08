#include "TIMGE/ApplicationBase.hpp"

#include <GLFW/glfw3.h>

namespace TIMGE
{
    ApplicationBase::ApplicationBase()
    {
        if (!glfwInit()) {
            throw "Failed to initialize GLFW";
        }
    }

    ApplicationBase::~ApplicationBase()
    {
        glfwTerminate();
    }
}

#ifndef TIMGE_APPLICATION_HPP
#define TIMGE_APPLICATION_HPP

#include <cstdint>
#include <string_view>

#include "ApplicationBase.hpp"
#include "Window.hpp"

namespace TIMGE
{
    class Application : public ApplicationBase
    {
        public:
            Application(const Window::Info& info);
            Application(std::string_view title, uint32_t width, uint32_t height);
            ~Application();

            virtual void Run() = 0;
            virtual void Update() = 0;
            virtual void Render() = 0;

            bool operator!() { return true; }
        public:
            Window mWindow;
    };
}

#endif // TIMGE_APPLICATION_HPP

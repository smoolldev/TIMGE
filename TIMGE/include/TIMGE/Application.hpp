#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "TIMGE/Window.hpp"
#include "TIMGE/Mouse.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <cstdint>
#include <string_view>

namespace TIMGE
{
   class ApplicationBase
    {
	public:
	    ApplicationBase();
	    virtual ~ApplicationBase() = 0;
	    virtual void Run() = 0;
	    virtual void Update() = 0;
	    virtual void Render() = 0;
    };

    class Application : public ApplicationBase
    {
	public:
	    struct Info
	    {
	        Window::Info mWindowInfo; // TODO: Change Window class
	        Vector<float, 4> mBackground;
	    };

	    Application(const Info& info);
	    Application(std::string_view title, uint32_t width, uint32_t height);
	    virtual ~Application() = 0;

	    virtual void Run() = 0;
	    virtual void Update() = 0;
	    virtual void Render() = 0;

	    virtual void BeginFrame();
	    virtual void EndFrame();

	    bool WindowShouldClose();
	    Window& GetWindow();
	private:
	    using EventProcessing_T = void(*)();
	protected:
	    static EventProcessing_T PollEvents;
	    static EventProcessing_T WaitEvents;
	private:
	    Info mInfo;
	    Window mWindow;
	};
}

#endif //APPLICATION_HPP

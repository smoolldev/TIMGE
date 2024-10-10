#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "TIMGE/Window.hpp"
#include <cstdint>
#include <string_view>

namespace TIMGE
{
    struct Color
    {
	float r,g,b,a;
    };

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
	        Color mBackground; // TODO: Vector
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
		  Window mWindow;
	private:
	    using EventProcessing_T = void(*)();
	protected:
	    static EventProcessing_T PollEvents;
	    static EventProcessing_T WaitEvents;
	private:
	    Info mInfo;
    };
}

#endif //APPLICATION_HPP

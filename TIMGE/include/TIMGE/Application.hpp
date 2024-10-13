#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "TIMGE/Window.hpp"
<<<<<<< HEAD
#include "TIMGE/Utils/Vector.hpp"
#include "TIMGE/CallbackDefs.hpp"
=======
#include "TIMGE/Mouse.hpp"
#include "TIMGE/Utils/Vector.hpp"
>>>>>>> 9f5873d (Fix: use new vector template and more)

#include <cstdint>
#include <string_view>

namespace TIMGE
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    class ApplicationBase
=======
   class ApplicationBase
>>>>>>> 3ed8b4d (Fix: use new vector template and more)
=======
    class ApplicationBase
>>>>>>> 976dddf (Fix TIMGESandbox stb_image linker error)
=======
=======
>>>>>>> 4c6a536 (Fix TIMGESandbox stb_image linker error)
=======
>>>>>>> 0fe6a1b (Fix TIMGESandbox stb_image linker error)
=======
>>>>>>> 2ce42e4 (Fix: use new vector template and more)
=======
>>>>>>> 955e532 (Fix TIMGESandbox stb_image linker error)
    class ApplicationBase
=======
   class ApplicationBase
>>>>>>> 9f5873d (Fix: use new vector template and more)
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 0bd3e2b (Fix: use new vector template and more)
=======
=======
    class ApplicationBase
>>>>>>> 4a45749 (Fix TIMGESandbox stb_image linker error)
<<<<<<< HEAD
>>>>>>> 4c6a536 (Fix TIMGESandbox stb_image linker error)
=======
   class ApplicationBase
>>>>>>> 3ed8b4d (Fix: use new vector template and more)
=======
    class ApplicationBase
>>>>>>> 976dddf (Fix TIMGESandbox stb_image linker error)
=======
    class ApplicationBase
=======
   class ApplicationBase
>>>>>>> 9f5873d (Fix: use new vector template and more)
>>>>>>> bbd11c1 (Fix: use new vector template and more)
=======
=======
    class ApplicationBase
>>>>>>> 4a45749 (Fix TIMGESandbox stb_image linker error)
>>>>>>> 0fe6a1b (Fix TIMGESandbox stb_image linker error)
=======
=======
=======
>>>>>>> 74efa8a (Fix TIMGESandbox stb_image linker error)
    class ApplicationBase
=======
   class ApplicationBase
>>>>>>> 3ed8b4d (Fix: use new vector template and more)
<<<<<<< HEAD
>>>>>>> 86d0e57 (Fix: use new vector template and more)
<<<<<<< HEAD
>>>>>>> 2ce42e4 (Fix: use new vector template and more)
=======
=======
=======
    class ApplicationBase
>>>>>>> 976dddf (Fix TIMGESandbox stb_image linker error)
>>>>>>> 74efa8a (Fix TIMGESandbox stb_image linker error)
>>>>>>> 955e532 (Fix TIMGESandbox stb_image linker error)
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
<<<<<<< HEAD
		Callback::Callbacks mCallbacks;
=======
>>>>>>> 9f5873d (Fix: use new vector template and more)
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
	public:
	    Info mInfo;
	    Window mWindow;
<<<<<<< HEAD
	    static Application* mInstance;

	    static Application* GetInstance(); 
	    friend void Callback::ErrorCallback(int errorCode, const char* description);
            friend void Callback::WindowPosCallback(GLFWwindow* window, int xPos, int yPos);
            friend void Callback::WindowSizeCallback(GLFWwindow* window, int width, int height);
            friend void Callback::WindowCloseCallback(GLFWwindow* window);
	    friend void Callback::WindowRefreshCallback(GLFWwindow *window);
            friend void Callback::WindowFocusCallback(GLFWwindow* window, int focused);
            friend void Callback::WindowIconifyCallback(GLFWwindow* window, int iconified);
            friend void Callback::WindowMaximizeCallback(GLFWwindow* window, int maximized);
            friend void Callback::FramebufferSizeCallback(GLFWwindow* window, int width, int height);
            friend void Callback::WindowContentScaleCallback(GLFWwindow* window, float xScale, float yScale);
            friend void Callback::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            friend void Callback::CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
            friend void Callback::CursorEnterCallback(GLFWwindow* window, int entered);
            friend void Callback::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
            friend void Callback::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            friend void Callback::CharCallback(GLFWwindow* window, unsigned int codepoint);
            friend void Callback::CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
            friend void Callback::DropCallback(GLFWwindow* window, int pathCount, const char* path[]);
            friend void Callback::MonitorCallback(GLFWmonitor* monitor, int event);
            friend void Callback::JoystickCallback(int jid, int event);
=======
>>>>>>> 9f5873d (Fix: use new vector template and more)
	};
}

#endif //APPLICATION_HPP

#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <cstdint>
#include <filesystem>

#include <GLFW/glfw3.h>
#include <vector>

#include "TIMGE/Window.hpp"

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
=======
=======
>>>>>>> 2ce42e4 (Fix: use new vector template and more)
=======
>>>>>>> 042ecf6 (Add Mouse Input Handling #11)
>>>>>>> 0db8b6c (Add Mouse Input Handling #11)
=======
<<<<<<< HEAD
>>>>>>> bbd11c1 (Fix: use new vector template and more)
=======
>>>>>>> 1f7c929 (Add Mouse Input Handling #11)
=======
>>>>>>> 0bd3e2b (Fix: use new vector template and more)
=======
=======
>>>>>>> fe6ef85 (Add Mouse Input Handling #11)
=======
=======
>>>>>>> f43d268 (Add Mouse Input Handling #11)
=======
>>>>>>> 86d0e57 (Fix: use new vector template and more)
=======
>>>>>>> 2ce42e4 (Fix: use new vector template and more)
    template<typename Type_T, uint32_t DIMENSIONS>
    struct Vector
    {
	Type_T mData[DIMENSIONS];
	Type_T& operator[](uint32_t index);
	const Type_T& operator[](uint32_t index) const;
    };

    template<typename Type_T, uint32_t DIMENSIONS>
    Type_T& Vector<Type_T, DIMENSIONS>::operator[](uint32_t index) {
	return mData[index];
    }

    template<typename Type_T, uint32_t DIMENSIONS>
    const Type_T& Vector<Type_T, DIMENSIONS>::operator[](uint32_t index) const {
	return mData[index];
    }

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> fe6ef85 (Add Mouse Input Handling #11)
=======
>>>>>>> 3ed8b4d (Fix: use new vector template and more)
=======
=======
>>>>>>> 0db8b6c (Add Mouse Input Handling #11)
>>>>>>> 3356953 (Add Mouse Input Handling #11)
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 1f7c929 (Add Mouse Input Handling #11)
=======
=======
>>>>>>> 9f5873d (Fix: use new vector template and more)
<<<<<<< HEAD
>>>>>>> 0bd3e2b (Fix: use new vector template and more)
=======
>>>>>>> fe6ef85 (Add Mouse Input Handling #11)
=======
>>>>>>> 3ed8b4d (Fix: use new vector template and more)
=======
>>>>>>> 3356953 (Add Mouse Input Handling #11)
>>>>>>> f43d268 (Add Mouse Input Handling #11)
=======
=======
>>>>>>> 9f5873d (Fix: use new vector template and more)
>>>>>>> bbd11c1 (Fix: use new vector template and more)
=======
=======
>>>>>>> fe6ef85 (Add Mouse Input Handling #11)
<<<<<<< HEAD
>>>>>>> 042ecf6 (Add Mouse Input Handling #11)
<<<<<<< HEAD
>>>>>>> 0db8b6c (Add Mouse Input Handling #11)
=======
=======
=======
>>>>>>> 3ed8b4d (Fix: use new vector template and more)
>>>>>>> 86d0e57 (Fix: use new vector template and more)
>>>>>>> 2ce42e4 (Fix: use new vector template and more)
    enum class StandardCursor
    {
	ARROW_CURSOR = GLFW_ARROW_CURSOR,
	IBEAM_CURSOR = GLFW_IBEAM_CURSOR,
	CROSSHAIR_CURSOR = GLFW_CROSSHAIR_CURSOR,
	POINTING_HAND_CURSOR = GLFW_POINTING_HAND_CURSOR,
	RESIZE_EW_CURSOR = GLFW_RESIZE_EW_CURSOR,
	RESIZE_NS_CURSOR = GLFW_RESIZE_NS_CURSOR,
	RESIZE_NWSE_CURSOR = GLFW_RESIZE_NWSE_CURSOR,
	RESIZE_NESW_CURSOR = GLFW_RESIZE_NESW_CURSOR,
	RESIZE_ALL_CURSOR = GLFW_RESIZE_ALL_CURSOR,
	NOT_ALLOWED_CURSOR = GLFW_NOT_ALLOWED_CURSOR,
    };

    struct Cursor
    {
	friend class Mouse;
	private:
	Cursor(uint64_t id) : mID{id} {}
	uint64_t mID;
    };

    class Mouse
    {
	public:
	    struct Info
	    {
		std::vector<std::filesystem::path> mCursorPaths;
	    };

	    Mouse(const Info& info, Window& window);
	    ~Mouse();

	    void Disable() const;
	    void Hide() const;
	    void Capture() const;
	    void Restore() const;
	    void EnableRawMouseMotion() const;
	    void DisableRawMouseMotion() const;

	    Cursor& AddCursor(const std::filesystem::path& image);
	    Cursor& AddCursor(StandardCursor shape);
	    void DeleteCursor(const Cursor& cursor);

	    void SetCursor(const Cursor& cursor);
	    void ResetCursor();

	    const Vector<double, 2>& GetPosition() const;
	    std::vector<Cursor*> GetCursors();
	private:
	    using RawMouseMotionSupported_t = int(*)();
	public:
	    static RawMouseMotionSupported_t IsRawMouseMotionSupported;
	private:
	    Window& mWindow;
	    Vector<double, 2> mPosition;
	    std::vector<std::pair<GLFWcursor*, Cursor>> mCursors;
    };
}

#endif //MOUSE_HPP

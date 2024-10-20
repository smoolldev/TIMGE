#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <cstdint>
#include <filesystem>

#include <vector>

#include "Window.hpp"

namespace TIMGE {
enum class StandardCursor {
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

enum class Button {
  ONE = GLFW_MOUSE_BUTTON_1,
  TWO = GLFW_MOUSE_BUTTON_2,
  THREE = GLFW_MOUSE_BUTTON_3,
  FOUR = GLFW_MOUSE_BUTTON_4,
  FIVE = GLFW_MOUSE_BUTTON_5,
  SIX = GLFW_MOUSE_BUTTON_6,
  SEVEN = GLFW_MOUSE_BUTTON_7,
  EIGHT = GLFW_MOUSE_BUTTON_8,
  LAST = GLFW_MOUSE_BUTTON_LAST,
  LEFT = GLFW_MOUSE_BUTTON_LEFT,
  RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
  MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
};

struct Cursor {
  friend class Mouse;

private:
  Cursor(uint64_t id) : mID{id} {}
  uint64_t mID;
};

class Mouse {
public:
  enum class Action { PRESSED = GLFW_PRESS, RELEASED = GLFW_RELEASE };

  struct Info {
    std::vector<std::filesystem::path> mCursorPaths;
  };

  Mouse(const Info &info, Window &window);
  ~Mouse();

  bool Pressed(Button button) const;
  bool Released(Button button) const;

  void Disable() const;
  void Hide() const;
  void Capture() const;
  void Restore() const;
  void EnableRawMouseMotion() const;
  void DisableRawMouseMotion() const;

  Cursor &AddCursor(const std::filesystem::path &image);
  Cursor &AddCursor(StandardCursor shape);
  void DeleteCursor(const Cursor &cursor);

  void SetCursor(const Cursor &cursor);
  void ResetCursor();

  const Vector<double, 2> &GetPosition() const;
  const Vector<double, 2> &GetOffset() const;

  std::vector<Cursor *> GetCursors();

private:
  using RawMouseMotionSupported_t = int (*)();

public:
  static RawMouseMotionSupported_t IsRawMouseMotionSupported;

private:
  Window &mWindow;

  Vector<double, 2> mPosition;
  Vector<double, 2> mOffset;

  std::vector<std::pair<GLFWcursor *, Cursor>> mCursors;

  friend class Application;
};
} // namespace TIMGE

#endif // MOUSE_HPP

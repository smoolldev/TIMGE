#include "TIMGE/Mouse.hpp"
#include "TIMGE/Window.hpp"

#include <filesystem>

#include <format>
#include <stb_image/stb_image.h>
#include <GLFW/glfw3.h>

namespace TIMGE
{
    MouseException::MouseException(std::string message)
     : Exception(std::format("Mouse: {}", message))
    {}

    Mouse::Mouse(const Info& info, Window& window)
     : mWindow{window}
    {
        for (const auto& path: info.mCursorPaths) {
            AddCursor(path);
        }
        if (!mCursors.empty()) {
            glfwSetCursor(window.mGetWindow(), mCursors[0].first);
        }
    }

    Mouse::~Mouse()
    {
        for (auto& cursor : mCursors) {
            glfwDestroyCursor(cursor.first);
        }
    }

    [[nodiscard]] bool Mouse::Pressed(Button button) const {
        return glfwGetMouseButton(mWindow.mGetWindow(), static_cast<int>(button)) == GLFW_PRESS;
    }

	[[nodiscard]] bool Mouse::Released(Button button) const {
        return glfwGetMouseButton(mWindow.mGetWindow(), static_cast<int>(button)) == GLFW_RELEASE;
    }

    void Mouse::Disable() const {
        glfwSetInputMode(mWindow.mGetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Mouse::Hide() const {
        glfwSetInputMode(mWindow.mGetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void Mouse::Capture() const {
        glfwSetInputMode(mWindow.mGetWindow(), GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
    }

    void Mouse::Restore() const {
        glfwSetInputMode(mWindow.mGetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    Mouse::RawMouseMotionSupported_t Mouse::IsRawMouseMotionSupported = glfwRawMouseMotionSupported;

    void Mouse::EnableRawMouseMotion() const {
        glfwSetInputMode(mWindow.mGetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    void Mouse::DisableRawMouseMotion() const {
        glfwSetInputMode(mWindow.mGetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    }

    [[maybe_unused]] Cursor& Mouse::AddCursor(const std::filesystem::path& image)
    {
        if (!std::filesystem::exists(image)) {
            throw MouseException(std::format("Cursor at \"{}\" doesn't exist!", image.string()));
        }
        GLFWimage icon;
        icon.pixels = stbi_load(image.string().c_str(), &icon.width, &icon.height, nullptr, 4);
        if (!icon.pixels) {
            throw MouseException("Something went wrong while loading cursor image!");
        }
        std::pair<GLFWcursor*, Cursor> cursor
        {
            glfwCreateCursor(&icon, 0, 0),
            mCursors.size()
        };
        if (!cursor.first) {
            throw MouseException("Something went wrong while creating cursor!");
        }
        mCursors.push_back(cursor);
        return mCursors.back().second;
    }

    [[maybe_unused]] Cursor& Mouse::AddCursor(StandardCursor shape)
    {
        std::pair<GLFWcursor*, Cursor> cursor
        {
            glfwCreateStandardCursor(static_cast<int>(shape)),
            mCursors.size()
        };
        if (!cursor.first) {
            throw MouseException("Something went wrong while creating standard cursor!");
        }
        mCursors.push_back(cursor);
        return mCursors.back().second;
    }

    void Mouse::DeleteCursor(const Cursor& cursor)
    {
        if (mCursors.empty()) {
            throw MouseException("Cannot delete a non-existing cursor.");
        }
        glfwDestroyCursor(mCursors[cursor.mID].first);
        if (cursor.mID != mCursors.size() - 1) {
            for (int i = cursor.mID + 1; i < mCursors.size(); i++) {
                mCursors[i].second.mID -= 1;
            }
        }
        mCursors.erase(mCursors.begin() + cursor.mID);
    }

    void Mouse::SetCursor(const Cursor& cursor) {
        glfwSetCursor(mWindow.mGetWindow(), mCursors[cursor.mID].first);
    }

    void Mouse::ResetCursor() {
        glfwSetCursor(mWindow.mGetWindow(), nullptr);
    }

    [[nodiscard]] const V2d& Mouse::GetPosition() const {
        return mPosition;
    }

    [[nodiscard]] const V2d& Mouse::GetOffset() const {
        return mOffset;
    }

    [[nodiscard]] std::vector<Cursor*> Mouse::GetCursors()
    {
        std::vector<Cursor*> result;
        for (auto& cursor: mCursors) {
            result.emplace_back(&cursor.second);
        }
        return result;
    }
}

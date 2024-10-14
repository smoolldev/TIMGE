#include "TIMGE/Mouse.hpp"
#include "TIMGE/Window.hpp"
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <filesystem>
#include <format>

namespace TIMGE
{
    Mouse::Mouse(const Info& info, Window& window)
     : mWindow{window}
    {
        for (const auto& path: info.mCursorPaths) {
            AddCursor(path);
        }
        if (!mCursors.empty()) {
            glfwSetCursor(window.GetWindow(), mCursors[0].first);
        }
    }

    Mouse::~Mouse()
    {
        glfwSetCursor(mWindow.GetWindow(), nullptr);
        for (auto& cursor : mCursors) {
            glfwDestroyCursor(cursor.first);
        }
    }

    bool Mouse::Pressed(Button button) const {
        return glfwGetMouseButton(mWindow.GetWindow(), static_cast<int>(button)) == GLFW_PRESS;
    }

	bool Mouse::Released(Button button) const {
        return glfwGetMouseButton(mWindow.GetWindow(), static_cast<int>(button)) == GLFW_RELEASE;
    }

    void Mouse::Disable() const {
        glfwSetInputMode(mWindow.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Mouse::Hide() const {
        glfwSetInputMode(mWindow.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void Mouse::Capture() const {
        glfwSetInputMode(mWindow.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
    }

    void Mouse::Restore() const {
        glfwSetInputMode(mWindow.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Mouse::EnableRawMouseMotion() const {
        glfwSetInputMode(mWindow.GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    void Mouse::DisableRawMouseMotion() const {
        glfwSetInputMode(mWindow.GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    }

    Cursor& Mouse::AddCursor(const std::filesystem::path& image)
    {
        if (!std::filesystem::exists(image)) {
            throw std::format("Path '{}' doesn't exist!\n", image.c_str()).c_str();
        }
        GLFWimage icon;
        icon.pixels = stbi_load(image.c_str(), &icon.width, &icon.height, nullptr, 4);
        if (!icon.pixels) {
            throw std::format("Something went wrong while loading '{}'!\n", image.c_str()).c_str();
        }
        std::pair<GLFWcursor*, Cursor> cursor{
            glfwCreateCursor(&icon, 0, 0),
            mCursors.size()
        };
        if (!cursor.first) {
            throw std::format("Something went wront while creating cursor: '{}'!\n", image.c_str()).c_str();
        }
        mCursors.push_back(cursor);
        return mCursors.back().second;
    }

    Cursor& Mouse::AddCursor(StandardCursor shape)
    {
        std::pair<GLFWcursor*, Cursor> cursor {
            glfwCreateStandardCursor(static_cast<int>(shape)),
            mCursors.size()
        };
        if (!cursor.first) {
            throw "Something went wront while creating standard cursor!\n";
        }
        mCursors.push_back(cursor);
        return mCursors.back().second;
    }

    void Mouse::DeleteCursor(const Cursor& cursor)
    {
        glfwDestroyCursor(mCursors[cursor.mID].first);
        if (cursor.mID != mCursors.size() - 1) {
            for (int i = cursor.mID + 1; i < mCursors.size(); i++) {
                mCursors[i].second.mID -= 1;
            }
        }
        if (mCursors.erase(mCursors.begin() + cursor.mID) == mCursors.end()) {
            throw "Fucking std::vector!\n";
        }
    }

    void Mouse::SetCursor(const Cursor& cursor) {
        glfwSetCursor(mWindow.GetWindow(), mCursors[cursor.mID].first);
    }

    void Mouse::ResetCursor() {
        glfwSetCursor(mWindow.GetWindow(), nullptr);
    }

    const Vector<double, 2>& Mouse::GetPosition() const {
        return mPosition;
    }

    const Vector<double, 2>& Mouse::GetOffset() const {
        return mOffset;
    }

    std::vector<Cursor*> Mouse::GetCursors()
    {
        std::vector<Cursor*> result;
        for (auto& cursor: mCursors) {
            result.emplace_back(&cursor.second);
        }
        return result;
    }

    Mouse::RawMouseMotionSupported_t Mouse::IsRawMouseMotionSupported = glfwRawMouseMotionSupported;
}

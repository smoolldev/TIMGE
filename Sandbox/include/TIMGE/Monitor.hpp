#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "Utils/Vector.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string_view>
#include <vector>

namespace TIMGE
{
    class Monitor
    {
        public:
            Monitor(const Monitor& monitor) = default;
            ~Monitor();

            static std::vector<Monitor*> GetMonitors();
            static Monitor* GetPrimaryMonitor();

            const Vector<int, 2>& GetPhysicalSize() const;
            const Vector<float, 2>& GetContentScale() const;
            const Vector<int, 2>& GetVirtualPosition() const;
            const Vector<int, 4>& GetWorkarea() const;

            const std::string_view& GetName() const;

            const float& GetGamma() const;

            void SetGamma(float gamma);
        private:
            Monitor(GLFWmonitor* monitor);

            GLFWmonitor* mGetMonitor() const;
            static void mRetrieveMonitors();

            static void Connect(GLFWmonitor* monitor);
            static void Disconnect(GLFWmonitor* monitor);

            GLFWmonitor* mMonitor;

            static std::vector<Monitor> mMonitors;

            Vector<int, 2> mPhysicalSize;
            Vector<float, 2> mContentScale;
            Vector<int, 2> mVirtualPosition;
            Vector<int, 4> mWorkarea;

            std::string_view mName;

            float mGamma;

            static bool mMonitorsRetrieved;

            friend class Application;
            friend class Window;
    };
}

#endif // MONITOR_HPP

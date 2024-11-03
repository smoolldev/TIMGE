#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "Exception.hpp"
#include "Utils/Vector.hpp"

#include <string_view>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TIMGE
{
    class MonitorException : public Exception
    {
        public:
            MonitorException(const std::string& message);
    };

    class Monitor
    {
        public:
            Monitor(const Monitor& monitor) = default;
            ~Monitor();

            [[nodiscard]] static const std::vector<Monitor>& GetMonitors();
            [[nodiscard]] static const Monitor& GetPrimaryMonitor();

            [[nodiscard]] const V2ui32& GetPhysicalSize() const;
            [[nodiscard]] const V2f& GetContentScale() const;
            [[nodiscard]] const V2i32& GetVirtualPosition() const;
            [[nodiscard]] const V2i32& GetWorkareaPosition() const;
            [[nodiscard]] const V2ui32& GetWorkareaSize() const;

            [[nodiscard]] const std::string_view& GetName() const;

            [[nodiscard]] const float& GetGamma() const;

            void SetGamma(float gamma);
        private:
            Monitor(GLFWmonitor* monitor);

            [[nodiscard]] GLFWmonitor* mGetMonitor() const;
            static void mRetrieveMonitors();
 
            void mRetrievePhysicalSize();
            void mRetrieveContentScale();
            void mRetrievePosition();
            void mRetrieveWorkarea();
            void mRetrieveName();

            static void mConnect(GLFWmonitor* monitor);
            static void mDisconnect(GLFWmonitor* monitor);

            GLFWmonitor* mMonitor;

            static std::vector<Monitor> mMonitors;

            static bool mMonitorsRetrieved;

            V2ui32 mPhysicalSize;
            V2f mContentScale;
            V2i32 mVirtualPosition;
            V2i32 mWorkareaPosition;
            V2ui32 mWorkareaSize;

            std::string_view mName;

            mutable float mGamma;

            friend class Application;
            friend class Window;
    };
}

#endif // MONITOR_HPP

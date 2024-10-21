#include "TIMGE/Monitor.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <algorithm>

#include <GLFW/glfw3.h>
#include <vector>

namespace TIMGE
{
    std::vector<Monitor> Monitor::mMonitors;

    bool Monitor::mMonitorsRetrieved = false;

    Monitor::Monitor(GLFWmonitor* monitor)
     : mMonitor{monitor},
       mGamma{1.0f}
    {
        glfwGetMonitorPhysicalSize(monitor, &mPhysicalSize[V2i32::WIDTH], &mPhysicalSize[V2i32::HEIGHT]);
        glfwGetMonitorContentScale(monitor, &mContentScale[V2f::X], &mContentScale[V2f::Y]);
        glfwGetMonitorPos(monitor, &mVirtualPosition[V2i32::X], &mVirtualPosition[V2i32::Y]);
        glfwGetMonitorWorkarea(monitor, &mWorkarea[V2i32::X], &mWorkarea[V2i32::Y], &mWorkarea[V2i32::WIDTH], &mWorkarea[V2i32::HEIGHT]);
        glfwGetMonitorName(monitor);
    }

    Monitor::~Monitor() {}

    [[nodiscard]] const std::vector<Monitor>& Monitor::GetMonitors()
    {
        if (!mMonitorsRetrieved)
        {
            mMonitorsRetrieved = true;
            mRetrieveMonitors();
        }

        return mMonitors;
    }

    const Monitor& Monitor::GetPrimaryMonitor()
    {
        if (!mMonitorsRetrieved)
        {
            mMonitorsRetrieved = true;
            mRetrieveMonitors();
        }

        if (mMonitors.empty()) {
            throw "no monitor for you fat fuck!\n";
        }

        return mMonitors[0];
    }

    [[nodiscard]] const V2i32& Monitor::GetPhysicalSize() const {
        return mPhysicalSize;
    }

	[[nodiscard]] const V2f& Monitor::GetContentScale() const {
        return mContentScale;
    }

	[[nodiscard]] const V2i32& Monitor::GetVirtualPosition() const {
        return mVirtualPosition;
    }

	[[nodiscard]] const V4i32& Monitor::GetWorkarea() const {
        return mWorkarea;
    }

    [[nodiscard]] const std::string_view& Monitor::GetName() const {
        return mName;
    }

	[[nodiscard]] const float& Monitor::GetGamma() const {
        return mGamma;
    }

	void Monitor::SetGamma(float gamma) const {
        glfwSetGamma(mMonitor, (mGamma = gamma));
    }

    void Monitor::mConnect(GLFWmonitor* monitor) {
        for (auto& _monitor : mMonitors)
        {
            if (_monitor.mMonitor == monitor) {
                return;
            }
        }

        mMonitors.push_back(static_cast<Monitor>(monitor));
    }

    void Monitor::mDisconnect(GLFWmonitor* monitor) {
        if (auto res = std::find_if(mMonitors.begin(), mMonitors.end(), [monitor](Monitor& m){ return m.mMonitor == monitor; }); res != mMonitors.end()) {
            mMonitors.erase(res);
        }
    }

    [[nodiscard]] GLFWmonitor* Monitor::mGetMonitor() const {
        for (auto& _monitor : mMonitors)
        {
            if (_monitor.mMonitor == mMonitor) {
                return mMonitor;
            }
        }

        return nullptr;
    }

    void Monitor::mRetrieveMonitors()
    {
        int monitorCount = 0;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

        for (int i = 0; i < monitorCount; i++)
        {
            if (monitors[i] == nullptr) {
                return;
            }

            mMonitors.push_back(monitors[i]);
        }
    }
}

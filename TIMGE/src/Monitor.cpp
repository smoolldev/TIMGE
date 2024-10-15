#include "TIMGE/Monitor.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <algorithm>

#include <GLFW/glfw3.h>
#include <vector>

namespace TIMGE
{
    bool Monitor::mMonitorsRetrieved = false;

    std::vector<Monitor> Monitor::mMonitors;

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

    std::vector<Monitor*> Monitor::GetMonitors()
    {
        if (!mMonitorsRetrieved)
        {
            mMonitorsRetrieved = true;
            mRetrieveMonitors();
        }

        std::vector<Monitor*> retVal;

        for (auto& monitor : mMonitors) {
            retVal.push_back(&monitor);
        }

        return retVal;
    }

    Monitor* Monitor::GetPrimaryMonitor()
    {
        if (!mMonitorsRetrieved)
        {
            mMonitorsRetrieved = true;
            mRetrieveMonitors();
        }

        if (mMonitors.empty()) {
            return nullptr;
        }

        return &mMonitors[0];
    }

    const Vector<int, 2>& Monitor::GetPhysicalSize() const {
        return mPhysicalSize;
    }

	const Vector<float, 2>& Monitor::GetContentScale() const {
        return mContentScale;
    }

	const Vector<int, 2>& Monitor::GetVirtualPosition() const {
        return mVirtualPosition;
    }

	const Vector<int, 4>& Monitor::GetWorkarea() const {
        return mWorkarea;
    }

    const std::string_view& Monitor::GetName() const {
        return mName;
    }

	const float& Monitor::GetGamma() const {
        return mGamma;
    }

	void Monitor::SetGamma(float gamma) {
        glfwSetGamma(mMonitor, (mGamma = gamma));
    }

    void Monitor::Connect(GLFWmonitor* monitor) {
        for (auto& _monitor : mMonitors)
        {
            if (_monitor.mMonitor == monitor) {
                return;
            }
        }

        mMonitors.push_back(static_cast<Monitor>(monitor));
    }

    void Monitor::Disconnect(GLFWmonitor* monitor) {
        if (auto res = std::find_if(mMonitors.begin(), mMonitors.end(), [monitor](Monitor& m){ return m.mMonitor == monitor; }); res != mMonitors.end()) {
            mMonitors.erase(res);
        }
    }

    GLFWmonitor* Monitor::mGetMonitor() const {
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

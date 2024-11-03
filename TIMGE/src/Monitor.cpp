#include "TIMGE/Monitor.hpp"
#include "TIMGE/Utils/Vector.hpp"

#include <algorithm>
#include <format>
#include <vector>

#include <GLFW/glfw3.h>

namespace TIMGE
{
    MonitorException::MonitorException(const std::string& message)
     : Exception(std::format("Monitor: {}", message))
    {}

    std::vector<Monitor> Monitor::mMonitors;

    bool Monitor::mMonitorsRetrieved = false;

    Monitor::Monitor(GLFWmonitor* monitor)
     : mMonitor{monitor},
       mGamma{1.0f}
    {
        mRetrievePhysicalSize();
        mRetrieveContentScale();
        mRetrievePosition();
        mRetrieveWorkarea();
        mRetrieveName();
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
            throw MonitorException("There are no monitors available.");
        }

        return mMonitors[0];
    }

    [[nodiscard]] const V2ui32& Monitor::GetPhysicalSize() const {
        return mPhysicalSize;
    }

	[[nodiscard]] const V2f& Monitor::GetContentScale() const {
        return mContentScale;
    }

	[[nodiscard]] const V2i32& Monitor::GetVirtualPosition() const {
        return mVirtualPosition;
    }

	[[nodiscard]] const V2i32& Monitor::GetWorkareaPosition() const {
        return mWorkareaPosition;
    }

    [[nodiscard]] const V2ui32& Monitor::GetWorkareaSize() const {
        return mWorkareaSize;
    }

    [[nodiscard]] const std::string_view& Monitor::GetName() const {
        return mName;
    }

	[[nodiscard]] const float& Monitor::GetGamma() const {
        return mGamma;
    }

	void Monitor::SetGamma(float gamma) {
        glfwSetGamma(mMonitor, (mGamma = gamma));
    }

    void Monitor::mRetrievePhysicalSize() {
        glfwGetMonitorPhysicalSize(
            mMonitor, 
            reinterpret_cast<int*>(&mPhysicalSize[V2ui32::WIDTH]), 
            reinterpret_cast<int*>(&mPhysicalSize[V2ui32::HEIGHT])
        );
    }

    void Monitor::mRetrieveContentScale() {
        glfwGetMonitorContentScale(mMonitor, &mContentScale[V2f::X], &mContentScale[V2f::Y]);
    }

    void Monitor::mRetrievePosition() {
        glfwGetMonitorPos(mMonitor, &mVirtualPosition[V2i32::X], &mVirtualPosition[V2i32::Y]);
    }

    void Monitor::mRetrieveWorkarea() {
        glfwGetMonitorWorkarea(mMonitor, 
            &mWorkareaPosition[V2i32::X], &mWorkareaPosition[V2i32::Y], 
            reinterpret_cast<int*>(&mWorkareaSize[V2i32::WIDTH]), 
            reinterpret_cast<int*>(&mWorkareaSize[V2i32::HEIGHT])
        );
    }

    void Monitor::mRetrieveName() {
        mName = glfwGetMonitorName(mMonitor);
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

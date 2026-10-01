#include "timeMonitor.h"

namespace seneca
{
    void TimeMonitor::startEvent(const char* name)
    {
        m_name = name;
        m_startTime = std::chrono::steady_clock::now();
    }

    Event TimeMonitor::stopEvent()
    {
        std::chrono::steady_clock::time_point endTime;
        std::chrono::nanoseconds duration;

        endTime = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
            endTime - m_startTime);

        return Event(m_name.c_str(), duration);
    }
}
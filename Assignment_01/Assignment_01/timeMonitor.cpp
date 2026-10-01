/***********************************************************************
Name: Alyssa Madrid
Seneca Email: amadrid1@myseneca.ca
Seneca Student ID: 103610259
Date Completed: October 1, 2026

I received assistance from AI while working on this
assignment. The assistance included reviewing the assignment
requirements and providing guidance/examples for the implementation of
Settings, Event, Logger, TimeMonitor, and Dictionary.

I reviewed and adapted the code for this assignment and tested it
against the provided tester.
***********************************************************************/
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
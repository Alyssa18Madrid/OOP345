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
#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <chrono>
#include <string>
#include "event.h"

namespace seneca
{
    class TimeMonitor
    {
        std::string m_name{};
        std::chrono::steady_clock::time_point m_startTime{};

    public:
        void startEvent(const char* name);
        Event stopEvent();
    };
}

#endif
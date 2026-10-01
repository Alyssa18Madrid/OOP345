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
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <string>
#include <chrono>

namespace seneca
{
    class Event
    {
        std::string m_name{};
        std::chrono::nanoseconds m_duration{};

    public:
        Event() = default;
        Event(const char* name, const std::chrono::nanoseconds& duration);

        friend std::ostream& operator<<(std::ostream& os, const Event& event);
    };
}

#endif
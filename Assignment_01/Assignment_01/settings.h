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
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <string>

namespace seneca
{
    struct Settings
    {
        bool m_show_all{ false };
        bool m_verbose{ false };
        std::string m_time_units{ "nanoseconds" };
    };

    extern Settings g_settings;
}

#endif
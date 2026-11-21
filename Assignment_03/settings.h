/***********************************************************************
Name: Alyssa Madrid
Seneca Email: amadrid1@myseneca.ca
Seneca Student ID: 103610259
Date Completed: November 20, 2026

I attempted the implementations of collection.cpp, spellChecker.cpp
myself, using the course notes for guidance.

I also asked AI for help implementing the CSV parsing helper in
record.h and using it in book.cpp, movie.cpp, and tvShow.cpp.
AI also helped implement and debug the episode duration parsing
in TvShow::readEpisode in tvShow.cpp.
***********************************************************************/
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <cstdint>

namespace seneca
{
    struct Settings
    {
        std::int16_t m_maxSummaryWidth{ 80 };
        bool m_tableView{ false };
    };

    extern Settings g_settings;
}

#endif
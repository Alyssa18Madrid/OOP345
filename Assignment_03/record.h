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
#ifndef SENECA_RECORD_H
#define SENECA_RECORD_H

#include <string>

namespace seneca
{
    inline std::string nextField(std::string& record, const char* error)
    {
        const auto comma = record.find(',');
        if (comma == std::string::npos)
            throw error;

        const auto field = record.substr(0, comma);
        record.erase(0, comma + 1);
        return field;
    }
}

#endif
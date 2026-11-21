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
#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <ostream>
#include <string>

namespace seneca
{
    class SpellChecker
    {
        static constexpr int WORD_COUNT = 6;
        std::string m_badWords[WORD_COUNT];
        std::string m_goodWords[WORD_COUNT];
        size_t m_counts[WORD_COUNT]{};

    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}

#endif
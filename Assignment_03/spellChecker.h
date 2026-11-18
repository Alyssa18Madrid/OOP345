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
#include "spellChecker.h"
#include <fstream>
#include <iomanip>

namespace seneca
{
    SpellChecker::SpellChecker(const char* filename)
    {
        std::ifstream file(filename);
        if (!file)
            throw "Bad file name!";

        for (int i = 0; i < WORD_COUNT; ++i)
            file >> m_badWords[i] >> m_goodWords[i];
    }

    void SpellChecker::operator()(std::string& text)
    {
        for (int i = 0; i < WORD_COUNT; ++i)
        {
            if (m_badWords[i].empty())
                continue;

            size_t position = text.find(m_badWords[i]);
            while (position != std::string::npos)
            {
                text.replace(position, m_badWords[i].size(), m_goodWords[i]);
                ++m_counts[i];
                position = text.find(m_badWords[i],
                    position + m_goodWords[i].size());
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const
    {
        for (int i = 0; i < WORD_COUNT; ++i)
        {
            out << std::right << std::setw(15) << std::setfill(' ')
                << m_badWords[i] << ": " << m_counts[i] << " replacements\n";
        }
    }
}
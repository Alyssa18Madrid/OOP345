#include "movie.h"
#include "record.h"
#include "settings.h"
#include <iomanip>

namespace seneca
{
    Movie::Movie(const std::string& title, const std::string& summary,
        unsigned short year)
        : MediaItem(title, summary, year)
    {
    }

    Movie* Movie::createItem(const std::string& line)
    {
        const char* error = "Not a valid movie.";
        auto record = line;
        trim(record);
        if (record.empty() || record.front() == '#')
            throw error;

        auto title = nextField(record, error);
        auto year = nextField(record, error);

        trim(title);
        trim(record);

        return new Movie(title, record, std::stoi(year));
    }

    // Display implementation supplied in the assignment.
    void Movie::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size())
                    <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(
                        0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7)
                << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(
                    pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-')
                << "" << std::setfill(' ') << '\n';
        }
    }
}
#include "book.h"
#include "record.h"
#include "settings.h"
#include <iomanip>

namespace seneca
{
    Book::Book(const std::string& title, const std::string& summary,
        unsigned short year, const std::string& author,
        const std::string& country, double price)
        : MediaItem(title, summary, year),
        m_author(author), m_country(country), m_price(price)
    {
    }

    Book* Book::createItem(const std::string& line)
    {
        const char* error = "Not a valid book.";
        auto record = line;
        trim(record);
        if (record.empty() || record.front() == '#')
            throw error;

        auto author = nextField(record, error);
        auto title = nextField(record, error);
        auto country = nextField(record, error);
        auto price = nextField(record, error);
        auto year = nextField(record, error);

        trim(author);
        trim(title);
        trim(country);
        trim(record);

        return new Book(title, record, std::stoi(year), author, country,
            std::stod(price));
    }

    // Display implementation supplied in the assignment.
    void Book::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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
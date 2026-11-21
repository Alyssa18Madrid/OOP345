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
#include "tvShow.h"
#include "record.h"
#include "settings.h"
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <sstream>

namespace seneca
{
    TvShow::TvShow(const std::string& title, const std::string& summary,
        unsigned short year, const std::string& id)
        : MediaItem(title, summary, year), m_id(id)
    {
    }

    TvShow* TvShow::createItem(const std::string& line)
    {
        const char* error = "Not a valid show.";
        auto record = line;
        trim(record);
        if (record.empty() || record.front() == '#')
            throw error;

        auto id = nextField(record, error);
        auto title = nextField(record, error);
        auto year = nextField(record, error);

        trim(id);
        trim(title);
        trim(record);

        return new TvShow(title, record, std::stoi(year), id);
    }

    // Display implementation supplied in the assignment.
    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7)
                << std::setfill('-') << "" << '\n';

            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(
                    pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(
                        pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }

            out << std::setw(this->getTitle().size() + 7) << std::setfill('-')
                << "" << std::setfill(' ') << '\n';
        }
    }

    TvEpisode TvShow::readEpisode(const std::string& line, std::string& id)
    {
        const char* error = "Not a valid episode.";
        std::string record = line;
        trim(record);

        if (record.empty() || record.front() == '#')
            throw error;

        id = nextField(record, error);
        trim(id);

        TvEpisode episode;
        episode.m_numberOverall = std::stoi(nextField(record, error));

        std::string season = nextField(record, error);
        trim(season);
        episode.m_season = season.empty() ? 1 : std::stoi(season);

        episode.m_numberInSeason = std::stoi(nextField(record, error));
        episode.m_airDate = nextField(record, error);
        trim(episode.m_airDate);

        std::istringstream duration(nextField(record, error));
        unsigned int hours{}, minutes{}, seconds{};
        char firstSeparator{}, secondSeparator{};

        if (!(duration >> hours >> firstSeparator >> minutes
            >> secondSeparator >> seconds)
            || firstSeparator != ':'
            || (secondSeparator != ':' && secondSeparator != '.'))
        {
            throw error;
        }

        episode.m_length = hours * 3600 + minutes * 60 + seconds;
        episode.m_title = nextField(record, error);
        trim(episode.m_title);
        trim(record);
        episode.m_summary = record;

        return episode;
    }

    double TvShow::getEpisodeAverageLength() const
    {
        if (m_episodes.empty())
            return 0.0;

        double total = std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
            [](double sum, const TvEpisode& episode)
            {
                return sum + episode.m_length;
            });

        return total / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const
    {
        std::vector<TvEpisode> longEpisodes;
        std::copy_if(m_episodes.begin(), m_episodes.end(),
            std::back_inserter(longEpisodes),
            [](const TvEpisode& episode)
            {
                return episode.m_length >= 3600;
            });

        std::list<std::string> titles;
        std::transform(longEpisodes.begin(), longEpisodes.end(),
            std::back_inserter(titles),
            [](const TvEpisode& episode)
            {
                return episode.m_title;
            });

        return titles;
    }
}
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include <list>
#include <vector>

namespace seneca
{
    class TvShow;

    struct TvEpisode
    {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem
    {
        std::string m_id;
        std::vector<TvEpisode> m_episodes;

        TvShow(const std::string& title, const std::string& summary,
            unsigned short year, const std::string& id);

        static TvEpisode readEpisode(const std::string& line, std::string& id);

    public:
        void display(std::ostream& out) const override;
        static TvShow* createItem(const std::string& line);

        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& line)
        {
            std::string id;
            auto episode = readEpisode(line, id);

            for (size_t i = 0; i < col.size(); ++i)
            {
                auto show = dynamic_cast<TvShow*>(col[i]);
                if (show && show->m_id == id)
                {
                    episode.m_show = show;
                    show->m_episodes.push_back(episode);
                    return;
                }
            }
        }

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };
}

#endif
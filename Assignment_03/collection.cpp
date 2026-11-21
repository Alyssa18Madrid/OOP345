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
#include "collection.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

namespace seneca
{
    Collection::Collection(const std::string& name) : m_name(name)
    {
    }

    const std::string& Collection::name() const
    {
        return m_name;
    }

    size_t Collection::size() const
    {
        return m_items.size();
    }

    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&))
    {
        m_observer = observer;
    }

    Collection& Collection::operator+=(MediaItem* item)
    {
        if (!item)
            return *this;

        std::unique_ptr<MediaItem> incoming(item);
        MediaItem* existing = (*this)[item->getTitle()];

        if (existing == item)
            incoming.release();
        else if (!existing)
        {
            m_items.push_back(std::move(incoming));
            if (m_observer)
                m_observer(*this, *item);
        }

        return *this;
    }

    MediaItem* Collection::operator[](size_t idx) const
    {
        if (idx >= size())
        {
            throw std::out_of_range("Bad index [" + std::to_string(idx)
                + "]. Collection has [" + std::to_string(size()) + "] items.");
        }

        return m_items[idx].get();
    }

    MediaItem* Collection::operator[](const std::string& title) const
    {
        auto match = std::find_if(m_items.begin(), m_items.end(),
            [title](const std::unique_ptr<MediaItem>& item)
            {
                return item->getTitle() == title;
            });

        return match == m_items.end() ? nullptr : match->get();
    }

    void Collection::removeQuotes()
    {
        auto stripQuotes = [](std::string text)
            {
                if (!text.empty() && text.front() == '"')
                    text.erase(0, 1);
                if (!text.empty() && text.back() == '"')
                    text.pop_back();

                return text;
            };

        std::for_each(m_items.begin(), m_items.end(),
            [stripQuotes](const std::unique_ptr<MediaItem>& item)
            {
                item->setTitle(stripQuotes(item->getTitle()));
                item->setSummary(stripQuotes(item->getSummary()));
            });
    }

    void Collection::sort(const std::string& field)
    {
        if (field != "title" && field != "year")
            return;

        std::sort(m_items.begin(), m_items.end(),
            [field](const std::unique_ptr<MediaItem>& first,
                const std::unique_ptr<MediaItem>& second)
            {
                if (field == "title")
                    return first->getTitle() < second->getTitle();

                return first->getYear() < second->getYear();
            });
    }

    std::ostream& operator<<(std::ostream& out, const Collection& collection)
    {
        for (size_t i = 0; i < collection.size(); ++i)
            out << *collection[i];

        return out;
    }
}
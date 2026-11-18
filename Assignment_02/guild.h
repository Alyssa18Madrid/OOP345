/***********************************************************************
Name: Alyssa Madrid
Seneca Email: amadrid1@myseneca.ca
Seneca Student ID: 103610259
Date Completed: October 16, 2026

I attempted the implementations of guild.cpp, team.cpp, and rogue.h
myself, using the course notes for guidance.

I also received AI-assistance for the implementations of CharacterTpl and Barbarian
along with debugging, simplification, and initial testing assistance.
***********************************************************************/
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <cstddef>
#include <string>
#include "character.h"

namespace seneca {

    class Guild {
        std::string m_name{};
        Character** m_members{};
        std::size_t m_size{};

        void swap(Guild& other) noexcept;

    public:
        Guild() = default;
        Guild(const char* name);

        Guild(const Guild& other);
        Guild& operator=(const Guild& other);

        Guild(Guild&& other) noexcept;
        Guild& operator=(Guild&& other) noexcept;

        ~Guild();

        void addMember(Character* c);
        void removeMember(const std::string& c);

        Character* operator[](std::size_t idx) const;
        void showMembers() const;
    };

}

#endif
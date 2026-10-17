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
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <cstddef>
#include <string>
#include "character.h"

namespace seneca {

    class Team {
        std::string m_name{};
        Character** m_members{};
        std::size_t m_size{};

        void swap(Team& other) noexcept;

    public:
        Team() = default;
        Team(const char* name);

        Team(const Team& other);
        Team& operator=(const Team& other);

        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;

        ~Team();

        void addMember(const Character* c);
        void removeMember(const std::string& c);

        Character* operator[](std::size_t idx) const;
        void showMembers() const;
    };

}

#endif
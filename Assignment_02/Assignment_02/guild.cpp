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
#include "guild.h"

namespace seneca {

    Guild::Guild(const char* name)
        : m_name(name ? name : "") {
    }

    Guild::Guild(const Guild& other)
        : m_name(other.m_name), m_size(other.m_size) {

        if (m_size > 0) {
            m_members = new Character * [m_size];

            // Guild copies refer to the same characters.
            for (std::size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i];
            }
        }
    }

    void Guild::swap(Guild& other) noexcept {
        m_name.swap(other.m_name);

        Character** members = m_members;
        m_members = other.m_members;
        other.m_members = members;

        std::size_t size = m_size;
        m_size = other.m_size;
        other.m_size = size;
    }

    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            Guild copy(other);
            swap(copy);
        }

        return *this;
    }

    Guild::Guild(Guild&& other) noexcept {
        swap(other);
    }

    Guild& Guild::operator=(Guild&& other) noexcept {
        if (this != &other) {
            delete[] m_members;

            m_members = other.m_members;
            m_size = other.m_size;
            m_name.swap(other.m_name);

            other.m_members = nullptr;
            other.m_size = 0;
            other.m_name.clear();
        }

        return *this;
    }

    Guild::~Guild() {
        // Characters belong to their teams, so only delete the array.
        delete[] m_members;
    }

    void Guild::addMember(Character* c) {
        if (c == nullptr) {
            return;
        }

        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;
            }
        }

        Character** members = new Character * [m_size + 1];

        for (std::size_t i = 0; i < m_size; ++i) {
            members[i] = m_members[i];
        }

        try {
            c->setHealthMax(c->getHealthMax() + 300);
        }
        catch (...) {
            delete[] members;
            throw;
        }

        members[m_size] = c;

        delete[] m_members;
        m_members = members;
        ++m_size;
    }

    void Guild::removeMember(const std::string& c) {
        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                m_members[i]->setHealthMax(
                    m_members[i]->getHealthMax() - 300
                );

                for (std::size_t j = i + 1; j < m_size; ++j) {
                    m_members[j - 1] = m_members[j];
                }

                --m_size;
                m_members[m_size] = nullptr;
                return;
            }
        }
    }

    Character* Guild::operator[](std::size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }

        return nullptr;
    }

    void Guild::showMembers() const {
        if (m_name.empty()) {
            std::cout << "No guild." << std::endl;
            return;
        }

        std::cout << "[Guild] " << m_name << std::endl;

        for (std::size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": "
                << *m_members[i] << std::endl;
        }
    }

}
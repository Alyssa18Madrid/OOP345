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
#include "team.h"

namespace seneca {

    Team::Team(const char* name)
        : m_name(name ? name : "") {
    }

    Team::Team(const Team& other)
        : m_name(other.m_name), m_size(other.m_size) {

        if (m_size > 0) {
            m_members = new Character * [m_size] {};

            try {
                for (std::size_t i = 0; i < m_size; ++i) {
                    m_members[i] = other.m_members[i]->clone();
                }
            }
            catch (...) {
                for (std::size_t i = 0; i < m_size; ++i) {
                    delete m_members[i];
                }

                delete[] m_members;
                throw;
            }
        }
    }

    void Team::swap(Team& other) noexcept {
        m_name.swap(other.m_name);

        Character** members = m_members;
        m_members = other.m_members;
        other.m_members = members;

        std::size_t size = m_size;
        m_size = other.m_size;
        other.m_size = size;
    }

    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            Team copy(other);
            swap(copy);
        }

        return *this;
    }

    Team::Team(Team&& other) noexcept {
        swap(other);
    }

    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            for (std::size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }

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

    Team::~Team() {
        for (std::size_t i = 0; i < m_size; ++i) {
            delete m_members[i];
        }

        delete[] m_members;
    }

    void Team::addMember(const Character* c) {
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
            members[m_size] = c->clone();
        }
        catch (...) {
            delete[] members;
            throw;
        }

        delete[] m_members;
        m_members = members;
        ++m_size;
    }

    void Team::removeMember(const std::string& c) {
        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                delete m_members[i];

                for (std::size_t j = i + 1; j < m_size; ++j) {
                    m_members[j - 1] = m_members[j];
                }

                --m_size;
                m_members[m_size] = nullptr;
                return;
            }
        }
    }

    Character* Team::operator[](std::size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }

        return nullptr;
    }

    void Team::showMembers() const {
        if (m_name.empty()) {
            std::cout << "No team." << std::endl;
            return;
        }

        std::cout << "[Team] " << m_name << std::endl;

        for (std::size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": "
                << *m_members[i] << std::endl;
        }
    }
} // namespace seneca
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
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"

namespace seneca {

    template <typename T>
    class CharacterTpl : public Character {
        int m_healthMax;
        T m_health{};

    public:
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax(healthMax) {
            m_health = healthMax;
        }

        void takeDamage(int dmg) override {
            m_health -= dmg;

            if (!this->isAlive()) {
                m_health = 0;

                std::cout << "    " << this->getName()
                    << " has been defeated!" << std::endl;
            }
            else {
                std::cout << "    " << this->getName()
                    << " took " << dmg << " damage, "
                    << getHealth() << " health remaining."
                    << std::endl;
            }
        }

        int getHealth() const override {
            return static_cast<int>(m_health);
        }

        int getHealthMax() const override {
            return m_healthMax;
        }

        void setHealth(int health) override {
            m_health = health;
        }

        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }
    };

}

#endif
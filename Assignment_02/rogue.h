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
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "health.h"
#include "weapons.h"
#include "abilities.h"

namespace seneca {

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense;
        int m_baseAttack;
        FirstAbility_t m_firstAbility{};
        SecondAbility_t m_secondAbility{};
        Dagger m_weapon{};

    public:
        Rogue(const char* name, int healthMax,
            int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax),
            m_baseDefense(baseDefense),
            m_baseAttack(baseAttack) {
        }

        int getAttackAmnt() const override {
            return static_cast<int>(
                m_baseAttack + 2 * static_cast<double>(m_weapon)
                );
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Rogue(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking "
                << enemy->getName() << "." << std::endl;

            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);

            int dmg = getAttackAmnt();
            m_firstAbility.transformDamageDealt(dmg);
            m_secondAbility.transformDamageDealt(dmg);

            std::cout << "    Rogue deals " << dmg
                << " melee damage!" << std::endl;

            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for "
                << dmg << " damage." << std::endl;

            std::cout << "    Rogue has a defense of "
                << getDefenseAmnt()
                << ". Reducing damage received." << std::endl;

            dmg -= getDefenseAmnt();

            if (dmg < 0) {
                dmg = 0;
            }

            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);

            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}

#endif
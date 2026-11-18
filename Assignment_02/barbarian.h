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
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include "health.h"
#include "weapons.h"
#include "abilities.h"

namespace seneca {

    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense;
        int m_baseAttack;
        Ability_t m_ability{};
        Weapon_t m_weapon[2];

    public:
        Barbarian(const char* name, int healthMax,
            int baseAttack, int baseDefense,
            Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax),
            m_baseDefense(baseDefense),
            m_baseAttack(baseAttack),
            m_weapon{ primaryWeapon, secondaryWeapon } {
        }

        int getAttackAmnt() const override {
            return static_cast<int>(
                m_baseAttack
                + static_cast<double>(m_weapon[0]) / 2
                + static_cast<double>(m_weapon[1]) / 2
                );
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Barbarian(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking "
                << enemy->getName() << "." << std::endl;

            m_ability.useAbility(this);

            int dmg = getAttackAmnt();
            m_ability.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg
                << " melee damage!" << std::endl;

            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for "
                << dmg << " damage." << std::endl;

            std::cout << "    Barbarian has a defense of "
                << getDefenseAmnt()
                << ". Reducing damage received." << std::endl;

            dmg -= getDefenseAmnt();

            if (dmg < 0) {
                dmg = 0;
            }

            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}

#endif
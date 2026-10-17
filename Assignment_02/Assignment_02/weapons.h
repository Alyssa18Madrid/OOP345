/***********************************************************************
Name: Alyssa Madrid
Seneca Email: amadrid1@myseneca.ca
Seneca Student ID: 103610259
Date Completed: October 16, 2026

I received assistance from AI while working on this assignment.
The assistance included reviewing the assignment requirements,
generating the implementation of CharacterTpl, Barbarian, Archer,
Rogue, Team, and Guild, and compiling and testing the code against
the provided tester and sample output. AI also performed additional
checks for copying, moving, member removal, and duplicate members.
***********************************************************************/
#ifndef SENECA_WEAPONS_H
#define SENECA_WEAPONS_H

namespace seneca
{
	// for simplicity, the logic associated with the weapons is kept trivial.

	struct BareHands {
		double m_damage = 5;
		operator double() const { return m_damage; }
	};

	struct Sword {
		double m_damage = 20;
		operator double() const { return m_damage; }
	};

	struct Axe {
		double m_damage = 22.5;
		operator double() const { return m_damage; }
	};

	struct Bow {
		double m_damage = 19.2;
		operator double() const { return m_damage; }
	};

	struct Crossbow {
		double m_damage = 56;
		operator double() const { return m_damage; }
	};

	struct Dagger {
		double m_damage = 12.8;
		operator double() const { return m_damage; }
	};
}
#endif

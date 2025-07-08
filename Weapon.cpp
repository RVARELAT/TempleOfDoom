//
//  Weapon.cpp
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/20/24.
//
#include <stdio.h>
#include "Weapon.h"
// Base Weapon class constructor
Weapon::Weapon(std::string name, int row, int col, int damage, int dexterity)
    : GameObject(name, row, col, ')'), m_damage(damage), m_dexterity(dexterity)  {
    // weapon has different action string depending on the weapon
    if (name == "mace") {
        m_action = "swings mace at";
    } else if (name == "short sword") {
        m_action = "slashes short sword at";
    } else if (name == "long sword") {
        m_action = "swings long sword at";
    } else if (name == "magic axe") {
        m_action = "chops magic axe at";
    } else if (name == "magic fangs of sleep") {
        m_action = "strikes magic fangs at";
    }
}
// Getters for weapon properties
int Weapon::getDamage() const {
    return m_damage;
}
int Weapon::getDexterity() const {
    return m_dexterity;
}
std::string Weapon::getAction() const {
    return m_action;
}
// Derived Mace class
Mace::Mace(int row, int col)
    : Weapon("mace", row, col, 2, 0) {}
// Derived ShortSword class
ShortSword::ShortSword(int row, int col)
    : Weapon("short sword", row, col, 2, 0) {}
// Derived LongSword class
LongSword::LongSword(int row, int col)
    : Weapon("long sword", row, col, 4, 2) {}
// Derived MagicAxe class
MagicAxe::MagicAxe(int row, int col)
    : Weapon("magic axe", row, col, 5, 5) {}
// Derived MagicFang class
MagicFang::MagicFang(int row, int col)
    : Weapon("magic fangs of sleep", row, col, 2, 3) {}


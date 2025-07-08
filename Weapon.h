//  Weapon.h
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/20/24.
//
#ifndef Weapon_h
#define Weapon_h
#include <string>
#include "GameObject.h"

// derived weapon class from gameObjects
class Weapon : public GameObject {
public:
    // constructpr
    Weapon(std::string name, int row, int col, int damage, int dexterity);
    // destructor
    virtual ~Weapon() {}
    // Getters for weapon members
    int getDamage() const;
    int getDexterity() const;
    std::string getAction() const;
private:
//    A damage amount, an integer used in determining how much damage is done to a defender who is hit (i.e., how much the defender's hit points decrease), using the following formula:
//        damagePoints = randInt(0, attackerStrength + weaponDamageAmount - 1);
    int m_damage;
//    A dexterity bonus, an integer used in determining whether an attacker using that weapon hits the defender, using the following formula:
//        attackerPoints = attackerDexterity + weaponDexterityBonus;
//        defenderPoints = defenderDexterity + defenderArmorPoints;
//        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
//            attacker has hit defender
    int m_dexterity;
//    An action string, which is used to help form the message displayed when one actor attacks another. This string is part of a message like "Player swings long sword at ..." or "the Goblin slashes short sword at ...".
    std::string m_action;
};

// Derived classes for each type of weapon
class Mace : public Weapon {
public:
    Mace(int row, int col);
};
class ShortSword : public Weapon {
public:
    ShortSword(int row, int col);
};
class LongSword : public Weapon {
public:
    LongSword(int row, int col);
};
class MagicAxe : public Weapon {
public:
    MagicAxe(int row, int col);
};
class MagicFang : public Weapon {
public:
    MagicFang(int row, int col);
};
#endif /* Weapon_h */


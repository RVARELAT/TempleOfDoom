//  Scroll.h
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/19/24.
#ifndef Scroll_h
#define Scroll_h
#include <string>
#include "GameObject.h"
#include "Actors.h"
class Player;
class Scroll : public GameObject {
public:
    // constructor
    Scroll(std::string name, int row, int col);
    // destrucor
    virtual ~Scroll();
    // Pure virtual function to be implemented by derived scroll classes
    virtual void applyEffect(Player* player) = 0;
private:
    std::string m_description;
};
// Derived classes for each type of scroll
class ScrollOfTeleportation : public Scroll {
public:
    ScrollOfTeleportation(int row, int col);
    void applyEffect(Player* player);
};
class ScrollOfImproveArmor : public Scroll {
public:
    ScrollOfImproveArmor(int row, int col);
    void applyEffect(Player* player);
};
class ScrollOfRaiseStrength : public Scroll {
public:
    ScrollOfRaiseStrength(int row, int col);
    void applyEffect(Player* player);
};
class ScrollOfEnhanceHealth : public Scroll {
public:
    ScrollOfEnhanceHealth(int row, int col);
    void applyEffect(Player* player);
};
class ScrollOfEnhanceDexterity : public Scroll {
public:
    ScrollOfEnhanceDexterity(int row, int col);
    void applyEffect(Player* player);
};
#endif /* Scroll_h */



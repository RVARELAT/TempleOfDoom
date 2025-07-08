//
//  Scroll.cpp
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/19/24.
#include <stdio.h>
#include "Scroll.h"
#include "Maze.h"
#include "utilities.h"

// Base Scroll class constructor
Scroll::Scroll(std::string name, int row, int col)
    : GameObject(name, row, col, '?') {
        
}
// destructor
Scroll::~Scroll() {
    
}

// Derived ScrollOfTeleportation class
ScrollOfTeleportation::ScrollOfTeleportation(int row, int col)
    : Scroll("scroll of teleportation", row, col) {
        
}
// apply effect on player
void ScrollOfTeleportation::applyEffect(Player* player) {
    // A scroll of teleportation: The player is randomly moved to another place in the level that is not occupied by a wall or a monster.
    while (true){
        int rand_y = randInt(1, 17);
        int rand_x = randInt(1, 69);
        // once an empty spot has been found
        if (player->get_maze()->get_char(rand_y, rand_x)  == ' '){
            player->setRow(rand_x);
            player->setCol(rand_y);
            player->get_maze()->get_messages().push_back("You feel your body wrenched in space and time.");
            return;
        }
    }
}

// Derived ScrollOfImproveArmor class
ScrollOfImproveArmor::ScrollOfImproveArmor(int row, int col)
    : Scroll("scroll of enhance armor", row, col) {
        
}
// apply effect on player
void ScrollOfImproveArmor::applyEffect(Player* player) {
    // A scroll of improve armor: The player's armor points are increased by a random integer from 1 to 3.
    player->setArmor(player->getArmor() + randInt(1, 3));
    player->get_maze()->get_messages().push_back("Your armor glows blue");
}


// Derived ScrollOfRaiseStrength class
ScrollOfRaiseStrength::ScrollOfRaiseStrength(int row, int col)
    : Scroll("scroll of strength", row, col) {
        
}

// apply effect on player
void ScrollOfRaiseStrength::applyEffect(Player* player) {
    // A scroll of raise strength: The player's strength points are increased by a random integer from 1 to 3.
    player->setStrength(player->getStrength() + randInt(1, 3));
    player->get_maze()->get_messages().push_back("Your muscles bulge");
}


// Derived ScrollOfEnhanceHealth class
ScrollOfEnhanceHealth::ScrollOfEnhanceHealth(int row, int col)
    : Scroll("scroll of enhance health", row, col) {
        
}

// apply effect on player
void ScrollOfEnhanceHealth::applyEffect(Player* player) {
    // A scroll of enhance health: The player's maximum hit point value is increased by a random integer from 3 to 8. This scroll does not affect the player's current number of hit points.
    player->setHitPoints(player->getHitPoints() + randInt(3, 8));
    player->get_maze()->get_messages().push_back("You feel your heart beating stronger.");
    
}


// Derived ScrollOfEnhanceDexterity class
ScrollOfEnhanceDexterity::ScrollOfEnhanceDexterity(int row, int col)
    : Scroll("scroll of enhance dexterity", row, col) {
}


void ScrollOfEnhanceDexterity::applyEffect(Player* player) {
    // A scroll of enhance dexterity: The player's dexterity is increased by 1.
    player->setDexterity(player->getDexterity() + 1);
    player->get_maze()->get_messages().push_back("You feel like less of a klutz.");
}


//
//  Actors.h
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/13/24.
//
#ifndef Actors_h
#define Actors_h
#include "utilities.h"
#include "GameObject.h"
#include "Scroll.h"
#include <string>
#include <iostream>
#include <vector>
class Maze;
class Weapon;
using namespace std;
// Since the player and the monsters share so many characteristics, let's classify them as actors. (BASE CLASS)
class Actor{
public:
    // constructor intiliaizes all private member variables
    Actor(int row, int col, int hitPoints, int armor, int strength, int dexterity, int sleepTime, Weapon* w, Maze* maze);
    // every base class must have a virtual destructor
    virtual ~Actor();
    // Getter functions
    int getRow() const;
    int getCol() const;
    int getHitPoints() const;
    int getArmor() const;
    int getStrength() const;
    int getDexterity() const;
    int getSleepTime() const;
    // Setter functions
    void setRow(int row);
    void setCol(int col);
    void setHitPoints(int hitPoints);
    void setArmor(int armor);
    void setStrength(int strength);
    void setDexterity(int dexterity);
    void setSleepTime(int sleepTime);
    void decreaseHitPoints(int hitpoints);
    // Other member functions
    // Pure virtual function for moving
    virtual void move(char movr) = 0;
    // Pure virtual function for attacking
    virtual void attack(Actor& target) = 0;
    // returns the actor weapon
    Weapon* returnWP() const;
    // sets the actor weapon
    void setWP(Weapon* wp);
    // get maze
    Maze* get_maze();
private:
    // The actor's current position on the level.
    int m_row;
    int m_col;
    // Hit points, an integer from 0 to 99 indicating how healthy the actor is. Hit points decrease when an attacker hits the actor. The actor dies when the hit points drop to 0 or less.
    int m_hitPoints;
    // Armor points, an integer from 0 to 99 specifying how well protected from attacks the actor is. The higher the number, the better the protection.
    int m_armor;
    // Strength points, an integer from 0 to 99 specifying how strong the actor is when attacking.
    int m_strength;
    // Dexterity points, an integer from 0 to 99 specifying how skilled the actor is at using a weapon or dodging an attack. The higher this number is, the more likely an actor will hit an opponent during battle or dodge being hit.
    int m_dexterity;
    // Sleep time, an integer from 0 to 9 indicating how long the actor will sleep.
    int m_sleepTime;
    // The weapon the actor is currently wielding.monsters and actors can have weapons
    Weapon *m_weapon;
    // which maze does the actor belong to
    Maze *m_maze;
};
// derived player class
class Player : public Actor {
public:
    // Constructor
    Player(int row, int col, Maze *maze);
    // Destructor
    virtual ~Player();
    // displays the inventory
    void inventory();
    // move the player
    virtual void move(char direction);
    // player attck
    void attack(Actor& target);
    // getter for inventory
    vector<GameObject*>& get_inventory();
    // remove object from player inventory
    void removeObjectInventory(GameObject *gone);
    // handles when player pick ups gameObject
    void handlePickup();
    // handles when we read a scroll
    void readInventoryInput(char input);
    // handles when we wield a weapon
    void wieldWeapon(char input);
    // sets the player weapon
    void setWeapon(int i);
private:
    // player position
    int col;
    int row;
    // player weapon
    Weapon *equip_weapon;
    // player inventory
    vector<GameObject*> m_inventory;
};

// Base class for Monsters (Abstract)
class Monster : public Actor{
public:
    // constructor
    Monster(int row, int col, int hitPoints, int armor, int strength, int dexterity, int sleepTime, Weapon* w, Maze *maze);
    // destructor
    virtual ~Monster();
    // can smell player function
    virtual bool canSmellPlayer(int distance) = 0;
    // uses the user input to move the player
    virtual void move(char direction) = 0;
    // player attck
    void attack(Actor& target) = 0;
    // get monster symbol
    virtual char get_symbol() = 0;
    // get monster name
    virtual string get_name() = 0;
private:
};

// B: derived bogeyman (Bogeymen appear only at temple level 2 or deeper)
class bogeyman : public Monster{
public:
    // constructor
    bogeyman(int row, int col, Maze *maze);
    // destructor
    virtual ~bogeyman();
    // bogeyman move
    virtual void move(char direction);
    // bogeyman attack
    virtual void attack(Actor& target);
    // can smell player
    virtual bool canSmellPlayer(int distance);
    // get monster symbol
    char get_symbol();
    // get monster name
    string get_name();
private:
    char symbol = 'B';
    string name = "Bogeyman";
};

// S: derived snakewomen (Snakewomen may appear on any temple level)
class snakewomen : public Monster{
public:
    // constructor
    snakewomen(int row, int col, Maze *maze);
    //destructor
    virtual ~snakewomen();
    virtual void move(char direction);
    virtual void attack(Actor& target);
    virtual bool canSmellPlayer(int distance);
    char get_symbol();
    string get_name();
private:
    char symbol = 'S';
    string name = "Snakewomen";
};


// D: derived dragon (Dragons appear only at temple level 3 or deeper)
class dragon : public Monster{
public:
    dragon(int row, int col, Maze *maze);
    // destructor
    virtual ~dragon();
    // note dragons do not mve
    virtual void move(char direction);
    virtual void attack(Actor& target);
    virtual bool canSmellPlayer(int distance);
    char get_symbol();
    string get_name();
private:
    char symbol = 'D';
    string name = "Dragon";
};

// G: derived goblin (Goblins may appear on any temple level)
class goblin : public Monster{
public:
    // constructor
    goblin(int row, int col, Maze *maze);
    //destructor
    virtual ~goblin();
    virtual void move(char direction);
    virtual void attack(Actor& target);
    virtual bool canSmellPlayer(int distance);
    char get_symbol();
    string get_name();
    // handles how the goblin will move using recursion
    int goblin_recursion(bool visited[][70], int goblin_row, int goblin_col, int smell_distance);
private:
    char symbol = 'G';
    string name = "Goblin";
};
#endif /* Actors_h */


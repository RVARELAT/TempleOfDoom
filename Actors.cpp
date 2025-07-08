//
//  Actors.cpp
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/13/24.
//
#include <stdio.h>
#include <iostream>
#include <algorithm>    // std::abs
#include "Actors.h"
#include "Weapon.h"
#include "Maze.h"

// constructor intiliaizes all private member variables
Actor::Actor(int row, int col, int hitPoints, int armor, int strength, int dexterity, int sleepTime, Weapon* w, Maze* maze)
        : m_row(row), m_col(col), m_hitPoints(hitPoints), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleepTime(sleepTime), m_weapon(w), m_maze(maze) {
    }

// every base class must have a virtual destructor
Actor::~Actor() {
    // monsters and player will derive this constructor
}

// Getter functions
int Actor::getRow() const { return m_row; }
int Actor::getCol() const { return m_col; }
int Actor::getHitPoints() const { return m_hitPoints; }
int Actor::getArmor() const { return m_armor; }
int Actor::getStrength() const { return m_strength; }
int Actor::getDexterity() const { return m_dexterity; }
int Actor::getSleepTime() const { return m_sleepTime; }

// Setter functions
void Actor::setRow(int row) { m_row = row; }
void Actor::setCol(int col) { m_col = col; }
void Actor::setHitPoints(int hitPoints) { m_hitPoints = hitPoints; }
void Actor::decreaseHitPoints(int hitpoints) { m_hitPoints -= hitpoints;}
void Actor::setArmor(int armor) { m_armor = armor; }
void Actor::setStrength(int strength) { m_strength = strength; }
void Actor::setDexterity(int dexterity) { m_dexterity = dexterity; }
void Actor::setSleepTime(int sleepTime) { m_sleepTime = sleepTime; }

// return the actor weapon
Weapon* Actor::returnWP() const{
    return m_weapon;
}
// set actor weapon
void Actor::setWP(Weapon* wp){
    m_weapon = wp;
}
// get the axctor maze
Maze* Actor::get_maze(){
    return m_maze;
}

// ---------------------------------- Player ---------------------------------------

// constructor for player
Player::Player(int row, int col, Maze *maze) : Actor(row,col,20,2,2,2,0, new ShortSword(row, col), maze){
    // intialize the players weapon and inventory to have short sword
    m_inventory.push_back(returnWP());
}

// Destructor (be careful with linking error)
Player::~Player(){
    // delete the invetory
    for (int i = 0; i < m_inventory.size(); i++){
        delete m_inventory[i];
    }
    m_inventory.clear();
}

// change players position based on movement
void Player::move(char direction){
    //move left
    if (direction == 'h'){
        setRow(getRow() - 1);
    }
    // move right
    if (direction == 'l'){
        setRow(getRow() + 1);
    }
    // move up
    if (direction == 'k'){
        setCol(getCol() - 1);
    }
    // move down
    if (direction == 'j'){
        setCol(getCol() + 1);
    }
}

// displays the player inventory
void Player::inventory(){
    clearScreen();
    cout << "Inventory:" << endl;
    char letter = 'a';
    // loop through inventory
    for (int i = 0; i < m_inventory.size(); i++){
        // different message for scroll in inventory
        if (m_inventory[i]->get_symbol() == '?'){
            cout << " " << letter << ". A scroll called " << m_inventory[i]->getName() << endl;
        }
        else{
            cout << " " << letter << ". " << m_inventory[i]->getName() << endl;
        }
        // set it to the next letter
        letter++;
    }
}

// player attack
void Player::attack(Actor& target){
}

// access the player vector
vector<GameObject*>& Player::get_inventory(){
    return m_inventory;
}

// handles when the player picks up an object
void Player::handlePickup(){
    // loop through the maze game objects
    for (auto i = get_maze()->get_gameObjects().begin(); i != get_maze()->get_gameObjects().end();){
        GameObject* curr_item = *i;
        // if we find the game object the player wants to pick up
        if (getCol() == curr_item->get_row() && getRow() == curr_item->get_col()){
            // push to the player messages vector
            this->get_maze()->get_messages().push_back("you pick up " + curr_item->getName());
            // add the player inventory
            m_inventory.push_back(curr_item);
            // erase the item after picking it up from the gameObjects vector
            i = get_maze()->get_gameObjects().erase(i);
        }
        else{
            // if its not the index at the game object, we update the iterator
            i++;
        }
    }
}

// remove object from player inventory
void Player::removeObjectInventory(GameObject *gone){
    // loop through inventory
    for (auto i = m_inventory.begin(); i != m_inventory.end(); ){
        // gameObject we want to remove
        if (*i == gone){
            delete *i;
            i = m_inventory.erase(i);
        }
        else{
            // increment iterator
            i++;
        }
    }
}

// read a scroll
void Player::readInventoryInput(char input){
    // convert their char input into an int
    char char_input = input - 'a';
    int int_input = char_input;
    // out of bounds input
    if (int_input < 0 || int_input >= m_inventory.size()){
        return;
    }
    // if they try to read a weapon
    if (m_inventory[int_input]->get_symbol() == ')'){
        this->get_maze()->get_messages().push_back("You can't read a " + m_inventory[int_input]->getName());
        return;
    }
    // they read a scroll
    if (m_inventory[int_input]->get_symbol() == '?'){
        // Dynamic cast
        GameObject* gp;
        gp = m_inventory[int_input];
        Scroll* sp = dynamic_cast<Scroll*>(gp);  // Try to convert gp
        if (sp != nullptr){  // if result is not null, sp really points to a Scroll
            // push message
            this->get_maze()->get_messages().push_back("You read the scroll called " + sp->getName());
            // aplly scroll effect to plyer
            sp->applyEffect(this);
            // delete and erase object from inventory
            removeObjectInventory(sp);
            return;
        }
        else{  // null result means gp pointed to some other kind of GameObject
            return;
        }
    }
}

// player wants to wield a weapon
void Player::wieldWeapon(char input){
    // convert their char input into an int
    char char_input = input - 'a';
    int int_input = char_input;
    // input out of bounds
    if (int_input < 0 || int_input >= m_inventory.size()){
        return;
    }
    // player tries to wield a scroll
    if (m_inventory[int_input]->get_symbol() == '?'){
        this->get_maze()->get_messages().push_back("You can't wield scroll of " + m_inventory[int_input]->getName());
    }
    // player wields a weapon
    if (m_inventory[int_input]->get_symbol() == ')'){
        // Dynamic cast
        GameObject* gp;
        gp = m_inventory[int_input];
        Weapon* wp = dynamic_cast<Weapon*>(gp);  // Try to convert gp
        if (wp != nullptr){  // if result is not null, wp really points to a Weapon
            // push message
            this->get_maze()->get_messages().push_back("You are wielding " + wp->getName());
            // change player weapon
            this->setWP(wp);
        }
        else{  // null result means gp pointed to some other kind of GameObject
            return;
        }
    }
}

// Monster --------------------------------------------

// constructor
Monster::Monster(int row, int col, int hitPoints, int armor, int strength, int dexterity, int sleepTime, Weapon* w, Maze *maze) : Actor(row, col, hitPoints, armor, strength, dexterity, sleepTime, w, maze){
    
}
// destructor
Monster::~Monster(){
}

// bogeyman --------------------------------------------------

// constructor
bogeyman::bogeyman(int row, int col, Maze *maze) : Monster(row, col, randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), 0, new ShortSword(row, col), maze){
    
}
// destructor
bogeyman::~bogeyman(){
    delete returnWP();
}

char bogeyman::get_symbol(){
    return symbol;
}

string bogeyman::get_name(){
    return name;
}

// move bogeyman
void bogeyman::move(char direction){
    // Skip turn if asleep
    if (getSleepTime() > 0) {
            return;
    }
    // get the player row and col m_grid[playerCol][playerRow]
    int playerRow = get_maze()->player()->getCol();
    int playerCol = get_maze()->player()->getRow();
    
    // is the smell distance in range (5 steps)
    if (abs(playerCol - this->getCol() + abs(playerRow - this->getRow())) > 5){
        return;
    }
    else{
        // move up
        if (getRow() < playerRow && get_maze()->taken_spot_by_actor(getRow() + 1, getCol()) == false){
            setRow(getRow() + 1);
            
        }
        // move down
        else if (getRow() > playerRow && get_maze()->taken_spot_by_actor(getRow() - 1, getCol()) == false){
            setRow(getRow() - 1);
            
        }
        // move right
        else if (getCol() < playerCol && get_maze()->taken_spot_by_actor(getRow(), getCol() + 1) == false){
            setCol(getCol() + 1);
            
        }
        // move left
        else if (getCol() > playerCol && get_maze()->taken_spot_by_actor(getRow(), getCol() - 1) == false){
            setCol(getCol() - 1);
            
        }
    }
}

void bogeyman::attack(Actor& target){
}

bool bogeyman::canSmellPlayer(int distance) {
    return false;
}

// snakewoman --------------------------

snakewomen::snakewomen(int row, int col, Maze* maze)
: Monster(row, col, randInt(3, 6), 3, 2, 3, 0, new MagicFang(row, col), maze){
    
}

snakewomen::~snakewomen(){
    delete returnWP();
}

char snakewomen::get_symbol(){
    return symbol;
}

string snakewomen::get_name(){
    return name;
}

void snakewomen::move(char direction){
    // Skip turn if asleep
    if (getSleepTime() > 0) {
            return;
    }
    // get the player row and col m_grid[playerCol][playerRow]
    int playerRow = get_maze()->player()->getCol();
    int playerCol = get_maze()->player()->getRow();
    
    // is the smell distance in range (3 steps)
    if (abs(playerCol - this->getCol() + abs(playerRow - this->getRow())) > 3){
        return;
    }
    else{
        // move up
        if (getRow() < playerRow && get_maze()->taken_spot_by_actor(getRow() + 1, getCol()) == false){
            setRow(getRow() + 1);
            
        }
        // move down
        else if (getRow() > playerRow && get_maze()->taken_spot_by_actor(getRow() - 1, getCol()) == false){
            setRow(getRow() - 1);
            
        }
        // move right
        else if (getCol() < playerCol && get_maze()->taken_spot_by_actor(getRow(), getCol() + 1) == false){
            setCol(getCol() + 1);
            
        }
        // move left
        else if (getCol() > playerCol && get_maze()->taken_spot_by_actor(getRow(), getCol() - 1) == false){
            setCol(getCol() - 1);
            
        }
    }
}



void snakewomen::attack(Actor& target){
    
}

bool snakewomen::canSmellPlayer(int distance) {
    return false;
}

// dragon -------------------------------------

dragon::dragon(int row, int col, Maze *maze)
: Monster(row, col, randInt(20, 25), 4, 4, 4, 0, new LongSword(row, col), maze){
    
}

dragon::~dragon(){
    delete returnWP();
}

// note monsters do not move
void dragon::move(char direction){
    
}

char dragon::get_symbol(){
    return symbol;
}

string dragon::get_name(){
    return name;
}

void dragon::attack(Actor& target){
    
}

bool dragon::canSmellPlayer(int distance) {
    return false;
}

// goblin -----------------------------

goblin::goblin(int row, int col, Maze *maze)
: Monster(row, col, randInt(15, 20), 1, 3, 1, 0, new ShortSword(row, col), maze){
    
}

goblin::~goblin(){
    delete returnWP();
}

char goblin::get_symbol(){
    return symbol;
}

string goblin::get_name(){
    return name;
}


void goblin::move(char direction){
    // goblin sleeping so can't move
   if (this->getSleepTime() > 0) {
           return;
   }
    // 4 grids set to false
    bool boolean_grid1[18][70] = {0};
    bool boolean_grid2[18][70] = {0};
    bool boolean_grid3[18][70] = {0};
    bool boolean_grid4[18][70] = {0};
    
    // check the what the outcome would be if we vist up, down, left, or right
    int up = goblin_recursion(boolean_grid1, this->getRow() - 1, this->getCol(), get_maze()->getGoblinSmellDistance() - 1);
    int down = goblin_recursion(boolean_grid2, this->getRow() + 1, this->getCol(), get_maze()->getGoblinSmellDistance() - 1);
    int left =  goblin_recursion(boolean_grid3, this->getRow(), this->getCol() - 1, get_maze()->getGoblinSmellDistance() - 1);
    int right = goblin_recursion(boolean_grid4, this->getRow(), this->getCol() + 1, get_maze()->getGoblinSmellDistance() - 1);
    
    // we move up if that is the optimal move
    if (up < 7000 && up <= right && up <= left && up <= down){
        // update the goblin to move up (if spot is open)
        if (get_maze()->taken_spot_by_actor(getRow() - 1, getCol()) == false){
            this->setRow(this->getRow() - 1);
        }
        return;
    }
    // we move down if that is the optimal move
    if (down < 7000 && down <= right && down <= left && down <= up){
        // update the goblin to move down (if spot is open)
        if (get_maze()->taken_spot_by_actor(getRow() + 1, getCol()) == false){
            this->setRow(this->getRow() + 1);
        }
        return;
    }
    
    // we move left if that is the optimal move
    if (left < 7000 && left <= right && left <= up && left <= down){
        // update the goblin to move left (if spot is open)
        if (get_maze()->taken_spot_by_actor(getRow(), getCol() - 1) == false){
            this->setCol(this->getCol() - 1);
        }
        return;
    }
    // we move right if that is the optimal move
    if (right < 7000 && right <= left && right <= down && right <= up){
        // update the goblin to move right (if spot is open)
        if (get_maze()->taken_spot_by_actor(getRow(), getCol() + 1) == false){
            this->setCol(this->getCol() + 1);
        }
        return;
    }
}

// returns number of steps
int goblin::goblin_recursion(bool visited[][70], int goblin_row, int goblin_col, int smell_distance){
    // get the player row and col m_grid[playerCol][playerRow]
    int playerRow = get_maze()->player()->getCol();
    int playerCol = get_maze()->player()->getRow();
    // is the goblin less than 15 (or goblin smell distance) steps away from the player
    if (smell_distance < 0){
        // no path within the smell distance, so we return some random large value (player is too far away)
        return 7000;
    }
    // base case: once the goblin reaches the player we return 0 as we need zero steps to reach the player
    if (goblin_row == playerRow && goblin_col == playerCol){
        return 0;
    }
    // check if spot was visited or something is at that spot (monster, wall)
    if (visited[goblin_row][goblin_col] == true || this->get_maze()->taken_spot_by_actor(goblin_row, goblin_col)){
        // path not possible, return random large number
        return 7000;
    }
    // mark the spot as discovered
    visited[goblin_row][goblin_col] = true;
    
    // check spot right (add +1 to keep track of the steps after every recursive call)
    int right = goblin_recursion(visited, goblin_row, goblin_col + 1, smell_distance - 1) + 1;
    // check spot left
    int left = goblin_recursion(visited, goblin_row, goblin_col - 1, smell_distance - 1) + 1;
    // check spot up
    int up = goblin_recursion(visited, goblin_row + 1, goblin_col, smell_distance - 1) + 1;
    // check spot down
    int down = goblin_recursion(visited, goblin_row - 1, goblin_col, smell_distance - 1) + 1;
    
    // make this spot false for future recursive calls
    visited[goblin_row][goblin_col] = false;
    
    // return the most optimal path
    if (up < down && up < right && up < left){
        return up;
    }
    else if (down < up && down < right && down < left){
        return down;
    }
    else if (right < down && right < up && right < left){
        return right;
    }
    else{
        return left;
    }
}


void goblin::attack(Actor& target){
    
}


bool goblin::canSmellPlayer(int distance) {
    return false;
}

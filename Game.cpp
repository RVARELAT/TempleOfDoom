//
//  Game.cpp
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/12/24.
//
#include "Game.h"
#include "utilities.h"
#include "Maze.h"
#include <iostream>
using namespace std;
// Implement these and other Game member functions you may have added.
Game::Game(int goblinSmellDistance){
    // construct the maze
    m_maze = new Maze();
    // pass this the goblin smell distance to the maze which will be used in the goblin move function
    m_maze->setGoblinSmellDistance(goblinSmellDistance);
}

// destructor
Game::~Game(){
    delete m_maze;
}

void Game::play(){
    // Create game and this function also adds a player
    // this function displays the maze
    m_maze->display_maze();
    
    while (true){
        // get the new command from the player
        char input = getCharacter();
        // quit the game
        if (input == 'q') {
            // maze destructor will be called which deletes gameObjects and Monsters and player
            cout << "Press q to exit game." << endl;
            break;
        }
        // no movement of player when it sleeps
        if (m_maze->player()->getSleepTime() > 0){
            // subtract from the sleep time after every move
            m_maze->player()->setSleepTime(m_maze->player()->getSleepTime() - 1);
            
            // get the player row and col
            int player_row = m_maze->player()->getCol();
            int player_col = m_maze->player()->getRow();
            
            // still have monster attack after player is sleeping
            if (m_maze->taken_spot_by_monster(player_row - 1, player_col)){
                m_maze->monster_attack(m_maze->player(), player_row - 1, player_col);
            }
            if (m_maze->taken_spot_by_monster(player_row + 1, player_col)){
                m_maze->monster_attack(m_maze->player(), player_row + 1, player_col);
            }
            if (m_maze->taken_spot_by_monster(player_row, player_col - 1)){
                m_maze->monster_attack(m_maze->player(), player_row, player_col - 1);
            }
            if (m_maze->taken_spot_by_monster(player_row, player_col)){
                m_maze->monster_attack(m_maze->player(), player_row, player_col + 1);
            }
            
            m_maze->display_maze();
            // // quit game when the player is dead
            if (m_maze->player()->getHitPoints() <= 0){
                for(int i = 0; i < m_maze->get_messages().size(); i++){
                      cout << m_maze->get_messages()[i] << endl;;
                  }
                break;
            }
            
            // cout the messages
            for(int i = 0; i < m_maze->get_messages().size(); i++){
                  cout << m_maze->get_messages()[i] << endl;;
            }
            m_maze->get_messages().clear();
            continue;
        }
        
        // get the players current position
        int r = m_maze->player()->getRow();
        int c = m_maze->player()->getCol();
        
        // the player wants to move left
        if(input == 'h'){
            // there is monster to the left of us that we want to attack
            if (m_maze->taken_spot_by_monster(c, r-1) == true){
                // player and monster attack
                m_maze->player_attack(m_maze->player(), c, r-1);
                m_maze->monster_attack(m_maze->player(), c, r-1);
                 
                m_maze->display_maze();
                // check if the monster killed the player
                if (m_maze->player()->getHitPoints() <= 0){
                    for(int i = 0; i < m_maze->get_messages().size(); i++){
                          cout << m_maze->get_messages()[i] << endl;;
                      }
                    break;
                }
                // cout the messages
                for(int i = 0; i < m_maze->get_messages().size(); i++){
                      cout << m_maze->get_messages()[i] << endl;;
                }
                m_maze->get_messages().clear();
                continue;
            }
                
            // if the player can move left
            else if (m_maze->taken_spot(c, r - 1) == false){
                // update the player position
                m_maze->player()->move('h');
                m_maze->move_monsters();
                // display the new maze
                m_maze->display_maze();
                continue;
            }
            else{
                // player shouldn't move
                m_maze->move_monsters();
                m_maze->display_maze();
                continue;
            }
        }
        // the player wants to move right
        if (input == 'l'){
            // there is monster to the right of us that we want to attack
            if (m_maze->taken_spot_by_monster(c, r+1) == true){
                // monster and player attack
                m_maze->player_attack(m_maze->player(), c, r+1);
                m_maze->monster_attack(m_maze->player(), c, r+1);

                m_maze->display_maze();
                // check if player died
                if (m_maze->player()->getHitPoints() <= 0){
                    for(int i = 0; i < m_maze->get_messages().size(); i++){
                          cout << m_maze->get_messages()[i] << endl;;
                      }
                    break;
                }
                // cout the messages
                for(int i = 0; i < m_maze->get_messages().size(); i++){
                      cout << m_maze->get_messages()[i] << endl;;
                  }
                m_maze->get_messages().clear();
                continue;
            }
            
            // if the player can move right
            if (m_maze->taken_spot(c, r + 1) == false){
                // update the player position
                m_maze->player()->move('l');
                m_maze->move_monsters();
                // display the new maze
                m_maze->display_maze();
                continue;
            }
            else{
                // player shpuldn't move
                m_maze->move_monsters();
                m_maze->display_maze();
                continue;
            }
        }
        // the player wants to move up
        if (input == 'k'){
            // there is monster above us that we want to attack
            if (m_maze->taken_spot_by_monster(c-1, r) == true){
                // monster and player attack
                m_maze->player_attack(m_maze->player(), c-1, r);
                m_maze->monster_attack(m_maze->player(), c-1, r);
                
                m_maze->display_maze();
                // check if monster killed the player
                if (m_maze->player()->getHitPoints() <= 0){
                    for(int i = 0; i < m_maze->get_messages().size(); i++){
                          cout << m_maze->get_messages()[i] << endl;;
                      }
                    break;
                }
                // cout the messages
                for(int i = 0; i < m_maze->get_messages().size(); i++){
                      cout << m_maze->get_messages()[i] << endl;;
                  }
                m_maze->get_messages().clear();
                continue;
            }
            // if the player can move up
            if (m_maze->taken_spot(c - 1, r) == false){
                // update the player position
                m_maze->player()->move('k');
                m_maze->move_monsters();
                // display the new maze
                m_maze->display_maze();
                continue;
            }
            else{
                m_maze->move_monsters();
                m_maze->display_maze();
                continue;
            }
        }
        // the player wants to move down
        if (input == 'j'){
            // there is monster to the below us that we want to attack
            if (m_maze->taken_spot_by_monster(c+1, r) == true){
                // monster and player attack
                m_maze->player_attack(m_maze->player(), c+1, r);
                
                m_maze->monster_attack(m_maze->player(), c+1, r);
                
                m_maze->display_maze();
                // check if monster killed the player
                if (m_maze->player()->getHitPoints() <= 0){
                    for(int i = 0; i < m_maze->get_messages().size(); i++){
                          cout << m_maze->get_messages()[i] << endl;;
                      }
                    break;
                }
                // cout the messages
                for(int i = 0; i < m_maze->get_messages().size(); i++){
                      cout << m_maze->get_messages()[i] << endl;;
                  }
                m_maze->get_messages().clear();
                continue;
            }
            
            // if the player can move down
            if (m_maze->taken_spot(c + 1, r) == false){
                // update the player position
                m_maze->player()->move('j');
                m_maze->move_monsters();
                // display the new maze
                m_maze->display_maze();
                continue;
            }
            else{
                // player shpuldn't move
                m_maze->move_monsters();
                m_maze->display_maze();
                continue;
            }
        }
        //the player inputs the stair
       if (input == '>'){
            // if the player is on top of the stair
            if (m_maze->atStair(c, r) == true){
                // delete the GameObjects and monsters in that level
                m_maze->deleteGameObjects();
                m_maze->deleteMonsters();
                m_maze->addLevel();
                // make a new maze
                m_maze->overrideMaze();
                m_maze->display_maze();
                continue;
            }
            else{
                // maze should not be changed in this case
                m_maze->move_monsters();
                m_maze->display_maze();
                continue;
            }
        }
       //the player inputs the golden idol
       if (input == 'g'){
            // if the player is on top of the golden idol
            if (m_maze->atGoldenIdol(c, r) == true){
                // player wins the game
                cout << endl;
                cout << "You picked up the golden idol" << endl;
                cout << "Congratulations, you won!" << endl;
                break;
            }
            // if the player is on top of a weapon
            if (m_maze->atGameObject(c, r) == true){
                // we only let the player pick up an item if inventory is not full
                if (m_maze->player()->get_inventory().size() < 26){
                    // we add the weapon to the inventory
                    m_maze->player()->handlePickup();
                    m_maze->move_monsters();
                    m_maze->display_maze();
                    // cout the messages
                    for(int i = 0; i < m_maze->get_messages().size(); i++){
                          cout << m_maze->get_messages()[i] << endl;;
                      }
                    m_maze->get_messages().clear();
                    continue;
                }
                else{
                    // player inventory is full
                    m_maze->move_monsters();
                    m_maze->display_maze();
                    cout << "Your knapsack is full; you can't pick that up." << endl;
                    continue;
                }
            }
            else{
                m_maze->move_monsters();
                m_maze->display_maze();
                continue;
            }
        }
        // see an inventory of your items
        if (input == 'i'){
            // display inventory
            m_maze->player()->inventory();
            m_maze->move_monsters();
            continue;
        }
        // read a scroll
        if (input == 'r'){
            // display inventory
            m_maze->player()->inventory();
            // get the user input again depending on what they want to read
            char new_input = getCharacter();
            m_maze->player()->readInventoryInput(new_input);
    
            m_maze->move_monsters();
            m_maze->display_maze();
            // cout the messages
            for(int i = 0; i < m_maze->get_messages().size(); i++){
                  cout << m_maze->get_messages()[i] << endl;;
              }
            m_maze->get_messages().clear();
            continue;
        }
        // wield a weapon
        if (input == 'w'){
            // display inventory
            m_maze->player()->inventory();
            // get the user input again depending on what they want to read
            char new_input = getCharacter();
            m_maze->player()->wieldWeapon(new_input);
            
            m_maze->move_monsters();
            m_maze->display_maze();
            
            // cout the messages
            for(int i = 0; i < m_maze->get_messages().size(); i++){
                  cout << m_maze->get_messages()[i] << endl;;
              }
            m_maze->get_messages().clear();
            continue;
        }
        
        //the player cheats
        if (input == 'c'){
            // increase hit points to max
            m_maze->player()->setHitPoints(99);
            // increase strength to 9 like sample version
            m_maze->player()->setStrength(9);
            m_maze->move_monsters();
            m_maze->display_maze();
            continue;
        }
        // if we get no matching input we just display maze again
        m_maze->move_monsters();
        m_maze->display_maze();
        // cout the messages
        for(int i = 0; i < m_maze->get_messages().size(); i++){
              cout << m_maze->get_messages()[i] << endl;;
          }
        m_maze->get_messages().clear();
    }
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons,
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.


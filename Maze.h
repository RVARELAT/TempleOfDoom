//
//  Maze.h
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/12/24.
//
#ifndef Maze_h
#define Maze_h

#include "utilities.h"
#include "Actors.h"
#include <string>
#include <vector>
class Player;
class Monster;
class GameObject;
const int MAXROWS = 18;               // max number of rows in a maze
const int MAXCOLS = 70;               // max number of columns in a maze

class Maze{
public:
    // Constructor to initialize maze dimensions
    Maze();
    // delete maze
    virtual ~Maze();
    // method to access the player
    Player* player() const;
    // get function to get char from mid
    char get_char(int r, int c);
    // Method to display the temple
    void display();
    // function to create rooms
    bool create_room(int room_number);
    // function to create hallways
    void create_hallways();
    // function to add the player
    void addPlayer();
    //check if the spot is movable to
    bool taken_spot(int r, int c);
    // adds a stair to the maze
    void addStair();
    // is there a stair at the current position
    bool atStair(int r, int c);
    // return maze level
    int getLevel();
    // set level
    void addLevel();
    // ovveride maze
    void overrideMaze();
    // add golden idol at final level
    void addGoldenIdol();
    // is there a golden at the current position
    bool atGoldenIdol(int r, int c);
    // monsters
    void addMonsters();
    // which monster do we create
    int whichMonster(int level, int row, int col, int i);
    // add game objects
    void addGameObjects();
    // which game object to create
    int whichGameObject(int row, int col, int i);
    // check if we are on top of a weapon
    bool atWeapon(int r, int c);
    // check if we are on top of a scroll
    bool atScroll(int r, int c);
    // what weapon are on
    char whatweapon(int row, int col);
    //are we at a game object
    bool atGameObject(int r, int c);
    // determine which game object
    GameObject* popGameObjectsAt(int c, int r);
    // delete monsters
    void deleteMonsters();
    // delete gameobjects
    void deleteGameObjects();
    // delete player
    void deletePlayer();
    // which object are we at
    std::string whichObject();
    // delete game object after picking it up
    void deleteGameObject(GameObject* remove_gameObject);
    // getter fpr gameObjects
    vector<GameObject*>& get_gameObjects();
    // show maze changes
    void showChanges();
    // dispay maze
    void display_maze();
    // spot taken by actor
    bool taken_spot_by_actor(int r, int c);
    // move monsters
    void move_monsters();
    // vector for string of messages
    vector<string>& get_messages();
    // display maze with no changes (just cout)
    void just_display_maze();
    // delete specfic monster
    void deleteMonster(Monster* remove_monster);
    // get monster in vector
    vector<Monster*>& get_monsters();
    // player attack
    void player_attack(Player* player, int r, int c);
    // taken spot by monster
    bool taken_spot_by_monster(int r, int c);
    // monster attack
    void monster_attack(Player* player, int r, int c);
    // is spot taken by player
    bool taken_spot_by_player(int r, int c);
    // getter for goblin smell distance
    int getGoblinSmellDistance();
    // set smell distance
    void setGoblinSmellDistance(int goblinSmellDistance);
    // goblin uses recursion to move
    int goblin_recursion(bool visited[][70], int goblin_row, int goblin_col, int smell_distance);
private:
    // grid private member variable (maze with 18 rows and 70 cols)
    char m_grid[MAXROWS][MAXCOLS];
    // player
    Player *m_player;
    // arrays for the center coords of the rooms created (y, x)
    int array_y[6];
    int array_x[6];
    // num of rooms
    int num_of_rooms;
    // stair position (first two ints in array)
    int stair_position_y[1];
    int stair_position_x[1];
    // golden Idol position (first two ints in array)
    int goldenIdol_position_y[1];
    int goldenIdol_position_x[1];
    // weapon positions
    int weapon_position_y[3];
    int weapon_position_x[3];
    // scroll postions
    int scroll_position_y[3];
    int scroll_position_x[3];
    // level starts at 0
    int m_level = 0;
    // monsters in maze
    std::vector<Monster*> monsters;
    // gameObjects in mazd
    std::vector<GameObject*> gameObjects;
    // messages that will be displayed
    std::vector<string> m_messages;
    // goblin smell distance passed by game constructor
    int m_goblinSmellDistance;
};
#endif /* Maze_h */


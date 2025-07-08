
//
//  Maze.cpp
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/12/24.
//

#include "Maze.h"
#include "GameObject.h"
#include "Weapon.h"
#include "Scroll.h"
#include <string>
#include <iostream>
using namespace std;

// constructor
Maze::Maze(){
    // Fill the grid with walls
    for (int r = 0; r < 18; r++){
        for (int c = 0; c < 70; c++){
            m_grid[r][c] = '#';
        }
    }
    // int of random rooms
    num_of_rooms = randInt(4, 6);
    // create the rooms until we are succesful
    for (int i = 0; i < num_of_rooms; ){
        int room_number = i;
        bool room = create_room(room_number);
        
        if (room == false){
            continue;
        }
        // only increment once we created a room succesfully
        i++;
   }
    // create hallways for the rooms
    create_hallways();
    // function to add a player after the rooms and hallways have been created
    addPlayer();
    // adds a stair to the maze only if we are at levels 0-3 (>)
    if (m_level == 0 || m_level == 1 || m_level == 2 || m_level == 3){
        addStair();
    }
    // add monsters
    addMonsters();
    // add gameObjects
    addGameObjects();
}

// destructor
Maze::~Maze(){
    // delete the game objects
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
    // delete the monsters
    for (int i = 0; i < monsters.size(); i++){
        delete monsters[i];
    }
    monsters.clear();
    // delete player
    delete m_player;
}

vector<GameObject*>& Maze::get_gameObjects(){
    return gameObjects;
}

vector<Monster*>& Maze::get_monsters(){
    return monsters;
}

vector<string>& Maze::get_messages(){
    return m_messages;
}

// function to call the monsters move functions
void Maze::move_monsters(){
    for (int i = 0; i < monsters.size(); i++){
        Monster *temp = monsters[i];
        temp->move('n');
    }
}

int Maze::getGoblinSmellDistance(){
    return m_goblinSmellDistance;
}

void Maze::setGoblinSmellDistance(int goblinSmellDistance){
    m_goblinSmellDistance = goblinSmellDistance;
}

// check if spot is taken by a monster
bool Maze::taken_spot_by_monster(int r, int c){
    for (int i = 0; i < monsters.size(); i++){
        Monster *temp = monsters[i];
        if ((temp->getRow() == r) && (temp->getCol() == c)){
            // spot is taken by a monster
            return true;
        }
    }
    return false;
}

// check if spot is taken by a player
bool Maze::taken_spot_by_player(int r, int c){
    if (r == m_player->getCol() && c == m_player->getCol()){
        return true;
    }
    return false;
}

// creates a new maze for a new level
void Maze::overrideMaze(){
    // Fill the grid with walls
    for (int r = 0; r < 18; r++){
        for (int c = 0; c < 70; c++){
            m_grid[r][c] = '#';
        }
    }
    // int of random rooms
    num_of_rooms = randInt(4, 6);
    // create the rooms until we are succesful
    for (int i = 0; i < num_of_rooms; ){
        int room_number = i;
        bool room = create_room(room_number);
        
        if (room == false){
            continue;
        }
        // only increment once we created a room succesfully
        i++;
   }
    // create hallways for the rooms
    create_hallways();
    // function to add a player after the rooms and hallways have been created
    int player_room = randInt(0, num_of_rooms - 1);
    // display the player in the center of a random room
    // Note we dont create a new player we just change its position
    m_player->setCol(array_y[player_room]);
    m_player->setRow(array_x[player_room]);
    // empty spot found
    if (m_grid[m_player->getCol()][m_player->getRow()] == ' '){
        m_grid[m_player->getCol()][m_player->getRow()] = '@';
    }
    // adds a stair to the maze only if we are at levels 0-3 (>)
    if (m_level == 0 || m_level == 1 || m_level == 2 || m_level == 3){
        addStair();
        addMonsters();
        addGameObjects();
    }
    // add a golden idol to the final level (&)
    if (m_level == 4){
        addGoldenIdol();
        addMonsters();
        addGameObjects();
    }
}

// redraw the grid after we make some changes (such as grabbing items)
void Maze::showChanges(){
    clearScreen();
    for (int r = 0; r < MAXROWS; r++){
        for (int c = 0; c < MAXCOLS; c++){
            // check if something was displayed at a position
            bool displayed = false;
            // display player
            if (r == m_player->getCol() && c == m_player->getRow()){
                m_grid[m_player->getCol()][m_player->getRow()] = '@';
                displayed = true;
                continue;
            }
            // we have a monster
            for (Monster* monster : monsters){
                if (r == monster->getRow() && monster->getCol()){
                    m_grid[monster->getRow()][monster->getCol()] = monster->get_symbol();
                    displayed = true;
                }
            }
            // dsiplay stair
            if (displayed == false && r == stair_position_y[0] && c == stair_position_x[0]){
                m_grid[r][c] = '>';
                displayed = true;
                continue;
            }
            // display golden idol
            if (displayed == false && r == goldenIdol_position_y[0] && c == goldenIdol_position_x[0]){
                m_grid[r][c] = '&';
                displayed = true;
                continue;
            }
            // display game objects
            for (GameObject *object : gameObjects){
                if (displayed == false && r == object->get_row() && c == object->get_col()){
                    if (object->get_symbol() == ')'){
                        m_grid[r][c] = ')';
                        displayed = true;
                        continue;
                    }
                    else if (object->get_symbol() == '?'){
                        m_grid[r][c] = '?';
                        displayed = true;
                        continue;
                    }
                }
            }
            // if nothing was displayed, this means we can simply display the wall or the empty space
            if (displayed == false){
                continue;
            }
        }
    }
}

void Maze::display_maze(){
    clearScreen();
    for (int r = 0; r < MAXROWS; r++){
        for (int c = 0; c < MAXCOLS; c++){
            // we have the player
            if (r == m_player->getCol() && c == m_player->getRow()){
                m_grid[m_player->getCol()][m_player->getRow()] = '@';
                continue;
            }
            // we have a monster
            for (Monster* monster : monsters){
                if (r == monster->getRow() && monster->getCol()){
                    m_grid[monster->getRow()][monster->getCol()] = monster->get_symbol();
                }
            }
            // check for stair
            if (m_level == 0 || m_level == 1 || m_level == 2 || m_level == 3){
                if (r == stair_position_y[0] && c == stair_position_x[0]){
                    m_grid[r][c] = '>';
                    continue;
                }
            }
            // check for golden idol
            if (m_level == 4){
                if (r == goldenIdol_position_y[0] && c == goldenIdol_position_x[0]){
                    m_grid[r][c] = '&';
                    continue;
                }
            }
            // check for game objects
            for (GameObject *object : gameObjects){
                if (r == object->get_row() && c == object->get_col()){
                    if (object->get_symbol() == ')'){
                        m_grid[r][c] = ')';
                        continue;
                        
                    }
                    else if (object->get_symbol() == '?'){
                        m_grid[r][c] = '?';
                        continue;
                    }
                }
            }
        }
    }
    
    // cout the maze
    for (int r = 0; r < 18; r++){
        for (int c = 0; c < 70; c++){
            cout << m_grid[r][c];
        }
        cout << endl;
    }
    // we leave the stair if we step over it
    if (m_player->getCol() == stair_position_y[0] && m_player->getRow() == stair_position_x[0]){
        m_grid[m_player->getCol()][m_player->getRow()] = '>';
    }
    // we leave the golden idol if we step over it
    else if (m_player->getCol() == goldenIdol_position_y[0] && m_player->getRow() == goldenIdol_position_x[0]){
        m_grid[m_player->getCol()][m_player->getRow()] = '&';
    }
    // change player previous visited postion to an empty space
    else {
        m_grid[m_player->getCol()][m_player->getRow()] = ' ';
    }
    // loop thrpough monsters
    // set their spots to empty after they move
    for (int i = 0; i < monsters.size(); i++){
        m_grid[monsters[i]->getRow()][monsters[i]->getCol()] = ' ';
    }
    // cout messages
    cout << "Level: " << getLevel() << ", Hit points: " << m_player->getHitPoints() << ", Armor: " << m_player->getArmor() << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDexterity() << endl;
    cout << endl;
}

// displays the maze
void Maze::display(){
    // draw the grid
    clearScreen();
    // add the new player position to the grid
    m_grid[m_player->getCol()][m_player->getRow()] = '@';
    // print out the grid
    for (int r = 0; r < 18; r++){
        for (int c = 0; c < 70; c++){
            cout << m_grid[r][c];
        }
        cout << endl;
    }
    // we leave the '>' if we step over it
    if (m_player->getCol() == stair_position_y[0] && m_player->getRow() == stair_position_x[0]){
        m_grid[m_player->getCol()][m_player->getRow()] = '>';
    }
    // we leave the golden idol if we step over it
    else if (m_player->getCol() == goldenIdol_position_y[0] && m_player->getRow() == goldenIdol_position_x[0]){
        m_grid[m_player->getCol()][m_player->getRow()] = '&';
    }
   // we leave the weapon or scroll if we step over it
    else if ((m_player->getCol() == weapon_position_y[0] && m_player->getRow() == weapon_position_x[0])
             || (m_player->getCol() == weapon_position_y[1] && m_player->getRow() == weapon_position_x[1])
             || (m_player->getCol() == weapon_position_y[2] && m_player->getRow() == weapon_position_x[2])){
            m_grid[m_player->getCol()][m_player->getRow()] = ')';
    }
    else if ((m_player->getCol() == scroll_position_y[0] && m_player->getRow() == scroll_position_x[0])
             || (m_player->getCol() == scroll_position_y[1] && m_player->getRow() == scroll_position_x[1])
             || (m_player->getCol() == scroll_position_y[2] && m_player->getRow() == scroll_position_x[2])){
            m_grid[m_player->getCol()][m_player->getRow()] = '?';
    }
    // leave space empty
    else{
        m_grid[m_player->getCol()][m_player->getRow()] = ' ';
    }
    
    // cout the messages
    cout << "Level: " << getLevel() << ", Hit points: " << m_player->getHitPoints() << ", Armor: " << m_player->getArmor() << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDexterity() << endl;
    cout << endl;
}

// simply couts the maze
void Maze::just_display_maze(){
    // print out the grid
    clearScreen();
    for (int r = 0; r < 18; r++){
        for (int c = 0; c < 70; c++){
            cout << m_grid[r][c];
        }
        cout << endl;
    }
    // cout the messages
    cout << "Level: " << getLevel() << ", Hit points: " << m_player->getHitPoints() << ", Armor: " << m_player->getArmor() << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDexterity() << endl;
    cout << endl;
}

// get char at maze position
char Maze::get_char(int r, int c){
    return m_grid[r][c];
}

//creates a room
bool Maze::create_room(int room_number){
    // upper left corner for room
    int rand_ul_x = randInt(2, 65);
    int rand_ul_y = randInt(2, 15);
    // random length and height
    int length = randInt(7, 11);
    int height = randInt(3, 10);
    // check if room is in bounds
    if (rand_ul_x + length > 68 || rand_ul_y + height > 16){
        return false;
    }
    // check if there is an overlapping room by checking if the inside of room is all walls
    for (int x = rand_ul_x - 1; x < length + rand_ul_x + 1; x++){
        for (int y = rand_ul_y - 1; y < height + rand_ul_y + 1; y++){
            if (m_grid[y][x] != '#'){
                return false;
            }
        }
    }
    // fill in the room with empty spaces
    for (int x = rand_ul_x; x < length + rand_ul_x; x++){
        for (int y = rand_ul_y; y < height + rand_ul_y; y++){
                m_grid[y][x] = ' ';
        }
    }
    // successful room was created in bounds
    // store its center x and y coord in an array to help us with creating hallways
    int coord_x = (rand_ul_x + (length / 2));
    int coord_y = (rand_ul_y + (height / 2));
    array_x[room_number] = coord_x;
    array_y[room_number] = coord_y;
    
    return true;
}

// create corridors connecting the rooms
void Maze::create_hallways(){
    // we don't create a hallway for the last room so we dont need to worry about its center coord
    for (int i = 0; i < num_of_rooms - 1; i++){
        // the the array whoch stores the center of the rooms to connect the corridors
        
        // make a hallway going up
        if (array_y[i] > array_y[i + 1]){
            for (int j = array_y[i]; j != array_y[i + 1]; j--){
                m_grid[j][array_x[i]] = ' ';
            }
        }
        // make a hallway going down
        else{
            for (int j = array_y[i]; j != array_y[i + 1]; j++){
                m_grid[j][array_x[i]] = ' ';
            }
        }
        // create a hallway going to the right
        if (array_x[i] < array_x[i + 1]){
            for (int j = array_x[i]; j != array_x[i + 1]; j++){
                m_grid[array_y[i + 1]][j] = ' ';
            }
        }
        // create a hallway going to the left
        else {
            for (int j = array_x[i]; j != array_x[i + 1]; j--){
                m_grid[array_y[i + 1]][j] = ' ';
            }
        }
    }
}

// function to add a player after the rooms and hallways have been created
void Maze::addPlayer(){
    // pick random a room to add the player
    int player_room = randInt(0, num_of_rooms - 1);
    // display the player in the center of a random room
    m_player = new Player(array_x[player_room], array_y[player_room], this);
    // spot should be empty hwere we place the player
    if (m_grid[m_player->getCol()][m_player->getRow()] == ' '){
        m_grid[m_player->getCol()][m_player->getRow()] = '@';
    }
}

// returns player
Player* Maze::player() const{
    return m_player;
}

// is maze spot taken by actor or wall
bool Maze::taken_spot_by_actor(int r, int c){
    // taken by wall
    if (m_grid[r][c] == '#'){
        return true;
    }
    // taken by monster
    for (int i = 0; i < monsters.size(); i++){
        Monster *temp = monsters[i];
        if ((temp->getRow() == r) && (temp->getCol() == c)){
            // spot is taken by a monster
            return true;
        }
    }
    // taken by player
    if (r == player()->getCol() && c == player()->getRow()){
        return true;
    }
    // spot is free
    return false;
}

// determines if grid spot is taken by wall
bool Maze::taken_spot(int r, int c){
    // spot is taken
    if (m_grid[r][c] == '#'){
        return true;
    }
    // spot not taken
    return false;
}
// add stair
void Maze::addStair(){
    while (true){
        // pick a random room to add the stairs
        int player_room = randInt(0, num_of_rooms - 1);
        // make sure spot is empty
        if (m_grid[array_y[player_room]][array_x[player_room]] == ' '){
            // store the stairs position in an array for y and x
            stair_position_y[0] = array_y[player_room];
            stair_position_x[0] = array_x[player_room];
            m_grid[array_y[player_room]][array_x[player_room]] = '>';
            break;
        }
    }
}

// check if we are at stair
bool Maze::atStair(int r, int c){
    if (r == stair_position_y[0] && c == stair_position_x[0]){
        return true;
    }
    else{
        return false;
    }
}

// add Golden Idol
void Maze::addGoldenIdol(){
    // pick a random room to add the golden idol
    while (true){
        int player_room = randInt(0, num_of_rooms - 1);
        if (m_grid[array_y[player_room]][array_x[player_room]] == ' '){
            goldenIdol_position_y[0] = array_y[player_room];
            goldenIdol_position_x[0] = array_x[player_room];
            m_grid[array_y[player_room]][array_x[player_room]] = '&';
            break;
        }
    }
}

// check if we are at Golden Idol
bool Maze::atGoldenIdol(int r, int c){
    if (m_grid[r][c] == '&'){
        return true;
    }
    else{
        return false;
    }
}

// increase level
void Maze::addLevel(){
    m_level++;
}

// return level
int Maze::getLevel(){
    return m_level;
}

// add gameobjects to maze
void Maze::addGameObjects(){
    // pick a number of game objects to add to the level
    int numOfGameObjects = randInt(2,3);
    // loop through number of gameObjects
    for (int i = 0; i < numOfGameObjects; i++){
        // add game object until we are succesful
        while (true){
            int rand_y = randInt(1, 17);
            int rand_x = randInt(1, 69);
            // once an empty spot has been found
            if (m_grid[rand_y][rand_x] == ' '){
                // call whichGameMonster will will create an object for us (returns 0 for weapon or 1 or scroll)
                int which_gameObject = whichGameObject(rand_y, rand_x, i);
                // add a weapon to the maze
                if (which_gameObject == 0){
                    m_grid[rand_y][rand_x] = ')';
                    // store the weapon posotion in an array for its x and y
                    weapon_position_y[i] = rand_y;
                    weapon_position_x[i] = rand_x;
                    break;
                }
                // add a scroll to the maze
                if (which_gameObject == 1){
                    m_grid[rand_y][rand_x] = '?';
                    // store the scroll posotion in an array for its x and y
                    scroll_position_y[i] = rand_y;
                    scroll_position_x[i] = rand_x;
                    break;
                }
            }
        }
    }
}

// pass in the row and col of where we want the object created as well as its index in the array
int Maze::whichGameObject(int row, int col, int i){
    // 0 - weapon 1 - scroll
     int rand_gameObject = randInt(0, 1);
    // if we want to add a weapon
    if (rand_gameObject == 0){
        // which weapon do we make
        // 0 - maces, 1 - Short words, 2 - Long Swords, 3 - Magic fangs of sleep, 4 - Magic axes
        int which_weapon = randInt(0, 4);
        // if we want to add a weapon
        if (which_weapon == 0){
            // add this game object to the maze
            Mace *temp = new Mace(row, col);
            gameObjects.push_back(temp);
            return 0;
        }
        if (which_weapon == 1){
            // add this game object to the maze
            ShortSword *temp = new ShortSword(row, col);
            gameObjects.push_back(temp);
            return 0;
        }
        if (which_weapon == 2){
            // add this game object to the maze
            LongSword *temp = new LongSword(row, col);
            gameObjects.push_back(temp);
            return 0;
        }
        if (which_weapon == 3){
            // add this game object to the maze
            MagicFang *temp = new MagicFang(row, col);
            gameObjects.push_back(temp);
            return 0;
        }
        if (which_weapon == 4){
            // add this game object to the maze
            MagicAxe *temp = new MagicAxe(row, col);
            gameObjects.push_back(temp);
            return 0;
        }
    }
    // if we want to add a scroll
    if (rand_gameObject == 1){
        // which scroll do we make
        // 0 - teleportation, 1 - improve armor, 2 - raise strength, 3 - enhance health, 4 - enhance dexterity
        int which_weapon = randInt(0, 4);
        // which scroll
        if (which_weapon == 0){
            // add this game object to the maze
            ScrollOfTeleportation *temp = new ScrollOfTeleportation(row, col);
            gameObjects.push_back(temp);
            return 1;
        }
        if (which_weapon == 1){
            // add this game object to the maze
            ScrollOfImproveArmor *temp = new ScrollOfImproveArmor(row, col);
            gameObjects.push_back(temp);
            return 1;
        }
        if (which_weapon == 2){
            // add this game object to the maze
            ScrollOfRaiseStrength *temp = new ScrollOfRaiseStrength(row, col);
            gameObjects.push_back(temp);
            return 1;
        }
        if (which_weapon == 3){
            // add this game object to the maze
            ScrollOfEnhanceHealth *temp = new ScrollOfEnhanceHealth(row, col);
            gameObjects.push_back(temp);
            return 1;
        }
        if (which_weapon == 4){
            // add this game object to the maze
            ScrollOfEnhanceDexterity *temp = new ScrollOfEnhanceDexterity(row, col);
            gameObjects.push_back(temp);
            return 1;
        }
    }
    // no gameObject created
    return -1;
}


// check if we are at weapon
bool Maze::atWeapon(int r, int c){
    if (m_grid[r][c] == ')'){
        return true;
    }
    else{
        return false;
    }
}

// check if we are at scroll
bool Maze::atScroll(int r, int c){
    if (m_grid[r][c] == '?'){
        return true;
    }
    else{
        return false;
    }
}

// add monsters to maze
void Maze::addMonsters(){
    // level 0 can have a goblin or a snakewoman
    if (getLevel() == 0){
        // formula given by spec to calculate how many monsters in level
        int m_nMonsters = randInt(2, 5*(0+1)+1);
        for (int i = 0; i < m_nMonsters; i++){
            while (true){
                int rand_y = randInt(1, 17);
                int rand_x = randInt(1, 69);
                // once an empty spot has been found
                if (m_grid[rand_y][rand_x] == ' '){
                    // pass in level 0 to whichMonster whill will create a monster for us
                    int which_monster = whichMonster(0, rand_y, rand_x, i);
                    // 0 - snakewomen, 1 - Goblin
                    if (which_monster == 0){
                        m_grid[rand_y][rand_x] = 'S';
                        break;
                    }
                    if (which_monster == 1){
                        m_grid[rand_y][rand_x] = 'G';
                        break;
                    }
                }
            }
        }
    }
    // level 1 can have a goblin or a snakewoman
    if (getLevel() == 1){
        // formula given by spec to calculate how many monsters in level
        int m_nMonsters = randInt(2, 5*(1+1)+1);
        for (int i = 0; i < m_nMonsters; i++){
            while (true){
                int rand_y = randInt(1, 17);
                int rand_x = randInt(1, 69);
                // once an empty spot has been found
                if (m_grid[rand_y][rand_x] == ' '){
                    // pass in level 0 to whichMonster whill will create a monster for us
                    int which_monster = whichMonster(1, rand_y, rand_x, i);
                    // 0 - snakewomen, 1 - Goblin
                    if (which_monster == 0){
                        m_grid[rand_y][rand_x] = 'S';
                        break;
                    }
                    if (which_monster == 1){
                        m_grid[rand_y][rand_x] = 'G';
                        break;
                    }
                }
            }
        }
    }
    // level 2 can have a goblin or a snakewoman or a bogeyman
    if (getLevel() == 2){
        // formula given by spec to calculate how many monsters in level
        int m_nMonsters = randInt(2, 5*(2+1)+1);
        for (int i = 0; i < m_nMonsters; i++){
            while (true){
                int rand_y = randInt(1, 17);
                int rand_x = randInt(1, 69);
                // once an empty spot has been found
                if (m_grid[rand_y][rand_x] == ' '){
                    // pass in level 0 to whichMonster whill will create a monster for us
                    int which_monster = whichMonster(2, rand_y, rand_x, i);
                    // 0 - snakewomen, 1 - Goblin 2 - Bogeyman
                    if (which_monster == 0){
                        m_grid[rand_y][rand_x] = 'S';
                        break;
                    }
                    if (which_monster == 1){
                        m_grid[rand_y][rand_x] = 'G';
                        break;
                    }
                    if (which_monster == 2){
                        m_grid[rand_y][rand_x] = 'B';
                        break;
                    }
                }
            }
        }
    }
    // level 3 can have a goblin or a snakewoman or a bogeyman or a dragon
    if (getLevel() == 3){
        // formula given by spec to calculate how many monsters in level
        int m_nMonsters = randInt(2, 5*(3+1)+1);
        for (int i = 0; i < m_nMonsters; i++){
            while (true){
                int rand_y = randInt(1, 17);
                int rand_x = randInt(1, 69);
                // once an empty spot has been found
                if (m_grid[rand_y][rand_x] == ' '){
                    // pass in level 0 to whichMonster whill will create a monster for us
                    int which_monster = whichMonster(3, rand_y, rand_x, i);
                    // 0 - snakewomen, 1 - Goblin 2 - Bogeyman 3 - Dragon
                    if (which_monster == 0){
                        m_grid[rand_y][rand_x] = 'S';
                        break;
                    }
                    if (which_monster == 1){
                        m_grid[rand_y][rand_x] = 'G';
                        break;
                    }
                    if (which_monster == 2){
                        m_grid[rand_y][rand_x] = 'B';
                        break;
                    }
                    if (which_monster == 3){
                        m_grid[rand_y][rand_x] = 'D';
                        break;
                    }
                }
            }
        }
    }
    // level 4 can have a goblin or a snakewoman or a bogeyman or a dragon
    if (getLevel() == 4){
        // formula given by spec to calculate how many monsters in level
        int m_nMonsters = randInt(2, 5*(4+1)+1);
        for (int i = 0; i < m_nMonsters; i++){
            while (true){
                int rand_y = randInt(1, 17);
                int rand_x = randInt(1, 69);
                // once an empty spot has been found
                if (m_grid[rand_y][rand_x] == ' '){
                    // pass in level 0 to whichMonster whill will create a monster for us
                    int which_monster = whichMonster(4, rand_y, rand_x, i);
                    // 0 - snakewomen, 1 - Goblin 2 - Bogeyman 3 - Dragon
                    if (which_monster == 0){
                        m_grid[rand_y][rand_x] = 'S';
                        break;
                    }
                    if (which_monster == 1){
                        m_grid[rand_y][rand_x] = 'G';
                        break;
                    }
                    if (which_monster == 2){
                        m_grid[rand_y][rand_x] = 'B';
                        break;
                    }
                    if (which_monster == 3){
                        m_grid[rand_y][rand_x] = 'D';
                        break;
                    }
                }
            }
        }
    }
}

// returns an int corresponding to a monster made
// 0 - snakewomen 1 - goblin 2 - bogeyman 3 - dragon
int Maze::whichMonster(int level, int row, int col, int i){
    // only gblin or snakeowman can appear
    if (level == 0 || level == 1){
        int rand = randInt(0, 1);
        if (rand == 0){
            // add this monster the monster vector
            monsters.push_back(new snakewomen(row, col, this));
            return 0;
        }
        if (rand == 1){
            // add this monster the monster vector
            monsters.push_back(new goblin(row, col, this));
            return 1;
        }
    }
    // bogeyman can mow appear
    if (level == 2){
        int rand = randInt(0, 2);
        if (rand == 0){
            // add this monster the monster vector
            monsters.push_back(new snakewomen(row, col, this));
            return 0;
        }
        if (rand == 1){
            // add this monster the monster vector
            monsters.push_back(new goblin(row, col, this));
            return 1;
        }
        if (rand == 2){
            // add this monster the monster vector
            monsters.push_back(new bogeyman(row, col, this));
            return 2;
        }
    }
    // dragon can now appear
    if (level == 3 || level == 4){
        int rand = randInt(0, 3);
        if (rand == 0){
            // add this monster the monster vector
            monsters.push_back(new snakewomen(row, col, this));
            return 0;
        }
        if (rand == 1){
            // add this monster the monster vector
            monsters.push_back(new goblin(row, col, this));
            return 1;
        }
        if (rand == 2){
            // add this monster the monster vector
            monsters.push_back(new bogeyman(row, col, this));
            return 2;
        }
        if (rand == 3){
            // add this monster the monster vector
            monsters.push_back(new dragon(row, col, this));
            return 3;
        }
    }
    // incorrect level argument creates no monsters
    return -1;
}


// check if we are at gameObject
bool Maze::atGameObject(int r, int c){
    for (int i = 0; i < gameObjects.size(); i++){
        GameObject *temp = gameObjects[i];
        // same rol and col as gamobject passed in
        if ((temp->get_row() == r) && (temp->get_col() == c)){
            return true;
        }
    }
    return false;
}


// helper function for when we want to know what gameObject is a a row and col
GameObject* Maze::popGameObjectsAt(int c, int r){
    for (int i = 0; i < gameObjects.size(); i++){
        GameObject *temp = gameObjects[i];
        // same gameObject as row and col passed in
        if ((temp->get_row() == c) && (temp->get_col() == r)){
            return temp;
        }
    }
    return nullptr;
}

// deletes Monsters at the level
void Maze::deleteMonsters(){
    for (int i = 0; i < monsters.size(); i++){
        delete monsters[i];
    }
    monsters.clear();
}

// deletes the game object at the level
void Maze::deleteGameObjects(){
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
}

// delete specfic game object from gameObject vector
void Maze::deleteGameObject(GameObject* remove_gameObject){
    for (auto i = gameObjects.begin(); i != gameObjects.end(); i++){
        // we have found the gameObject to delete
        if (*i == remove_gameObject){
            delete *i;
            // note erase returns a pointer to the next element
            i = gameObjects.erase(i);
            return;
        }
    }
}

// delete specfic monster from monster vector
void Maze::deleteMonster(Monster* remove_monster){
    for (auto i = monsters.begin(); i != monsters.end(); i++){
        // we have found the monster to delete
        if (*i == remove_monster){
            delete *i;
            // note erase returns a pointer to the next element
            i = monsters.erase(i);
            return;
        }
    }
}

// function that handles the player attack
void Maze::player_attack(Player* player, int r, int c){
    int monster_index = -1;
    // we must first identify what monster is next to player
    for (int i = 0; i < monsters.size(); i++){
        Monster *temp = monsters[i];
        if ((temp->getRow() == r) && (temp->getCol() == c)){
            // get the index of the monster we are next to
            monster_index = i;
        }
    }
    // no monster identified
    if (monster_index == -1){
        return;
    }
    // get the monster based on the index
    Monster* monster = monsters[monster_index];
    // A dexterity bonus, an integer used in determining whether an attacker using that weapon hits the defender, using the following formula:
    int defend_monsterpts = monster->getDexterity() + monster->getArmor();
    int attack_playerpts = m_player->returnWP()->getDexterity() + m_player->getDexterity();
    // attacker has hit defender
    if (randInt(1, attack_playerpts) >= randInt(1, defend_monsterpts)){
        // A damage amount, an integer used in determining how much damage is done to a defender who is hit (i.e., how much the defender's hit points decrease), using the following formula:
        int damage_points = randInt(0, player->getStrength() + player->returnWP()->getDamage() - 1);
        // decerease the monsterhitpoints
        monster->decreaseHitPoints(damage_points);
        
        // In addition to the regular hit point damage magic fangs of sleep do when the attacker hits the defender, there is a 1 in 5 chance that the magic fangs of sleep will put the defender to sleep. The number of moves the sleep will last (the sleep time) is a random integer from 2 to 6, call it X. If the defender is already asleep, with current sleep time Y, then the defender's sleep time becomes the maximum of X and Y (and not, say, Y+X).
        if (player->returnWP()->getName() == "magic fangs of sleep"){
            // 1 in 5 chance
            bool prob = trueWithProbability(0.2);
            if (prob == true){
                // random sleep time
                int new_sleep_time = randInt(2,6);
                int old_sleep_time = monster->getSleepTime();
                // new_sleep_time is greater
                if (new_sleep_time > old_sleep_time){
                    // set sleep time
                    monster->setSleepTime(new_sleep_time);
                }
                //  // we have a succesful attack with magic fangs and slept monster
                m_messages.push_back("Player " + player->returnWP()->getAction() + " the " + monster->get_name() + " and hits, putting " + monster->get_name() + " to sleep." );
            }
            else{
                // we have a succesful attack with magic fangs but didnt sleep monster
                m_messages.push_back("Player " + player->returnWP()->getAction() + " the " + monster->get_name() + " and hits.");
            }
        }
        
        // we have a succesful attack
        else{
            if (monster->getHitPoints() <= 0){
                m_messages.push_back("Player " + player->returnWP()->getAction() + " the " + monster->get_name() + + " dealing a final blow.");
            }
            else{
                m_messages.push_back("Player " + player->returnWP()->getAction() + " the " + monster->get_name() + " and hits.");
            }
        }
        
        // monster has been killed
        if (monster->getHitPoints() <= 0){
            // When a bogeyman dies, there is a 1 in 10 chance it will drop a magic axe if there is no item at the position where it dies.
            if (monster->get_symbol() == 'B'){
                bool drop_prob = trueWithProbability(0.2);
                if (drop_prob == true){
                    // add to game object array
                    gameObjects.push_back(new MagicAxe(r, c));
                }
            }
            // When a snakewoman dies, there is a 1 in 3 chance she will drop her magic fangs of sleep if there is no item at the position where she dies.
            if (monster->get_symbol() == 'S'){
                bool drop_prob = trueWithProbability(1.0/3.0);
                if (drop_prob == true){
                    // add to game object array
                    gameObjects.push_back(new MagicFang(r, c));
                }
            }
        
            // When a goblin dies, there is a 1 in 3 chance it will drop either a magic axe or magic fangs of sleep if there is no item at the position where it dies.
            if (monster->get_symbol() == 'G'){
                bool drop_prob = trueWithProbability(1.0/3.0);
                if (drop_prob == true){
                    int random_weapon = randInt(1, 2);
                    // add to game object array
                    if (random_weapon == 1){
                        gameObjects.push_back(new MagicFang(r, c));
                    }
                    else if (random_weapon == 2){
                        gameObjects.push_back(new MagicAxe(r, c));
                    }
                }
            }
                
            // When a dragon dies, there is a 100% chance it will drop a scroll of some kind if there is no item at the position where it dies.
            if (monster->get_symbol() == 'D'){
                int random_scroll = randInt(1, 5);
                if (random_scroll == 1){
                    gameObjects.push_back(new ScrollOfTeleportation(r, c));
                }
                else if (random_scroll == 2){
                    gameObjects.push_back(new ScrollOfImproveArmor(r, c));
                }
                else if (random_scroll == 3){
                    gameObjects.push_back(new ScrollOfRaiseStrength(r, c));
                }
                else if (random_scroll == 4){
                    gameObjects.push_back(new ScrollOfEnhanceHealth(r, c));
                }
                else if (random_scroll == 5){
                    gameObjects.push_back(new ScrollOfEnhanceDexterity(r, c));
                }
            }
            //delete the monster from the monsters array since its been killed
            deleteMonster(monster);
        }
    }
    else{
        // player did not hit the monster
        m_messages.push_back("Player " + player->returnWP()->getAction() + " the " + monster->get_name() + " and misses.");
    }
}

// function that handles the monster attack
void Maze::monster_attack(Player* player, int r, int c){
    
    // A dexterity bonus, an integer used in determining whether an attacker using that weapon hits the defender, using the following formula:
    int monster_index = -1;
       //Identify which monster is next to you
       for (int i = 0; i < monsters.size(); i++){
           int monster_row = monsters[i]->getRow();
           int monster_col = monsters[i]->getCol();
           if (monster_row == r && monster_col == c)
               monster_index = i;
       }
    // no mosnter detected
    if (monster_index == -1){
        return;
    }
    
    // monster we are next to based on index
    Monster* monster = monsters[monster_index];
    
    // if monster is asleep monster shouldnt attack
    if (monster->getSleepTime() > 0){
        monster->setSleepTime(monster->getSleepTime() - 1);
        return;
    }
    
    // A dexterity bonus, an integer used in determining whether an attacker using that weapon hits the defender, using the following formula:
    int defend_playerpts = m_player->getDexterity() + m_player->getArmor();
    int attack_monsterpts = monster->returnWP()->getDexterity() + monster->getDexterity();
    // attacker has hit defender
    if (randInt(1, attack_monsterpts) >= randInt(1, defend_playerpts)){
        // A damage amount, an integer used in determining how much damage is done to a defender who is hit (i.e., how much the defender's hit points decrease), using the following formula:
        int damage_points = randInt(0, monster->getStrength() + monster->returnWP()->getDamage() - 1);
        // decerease the player hit points
        m_player->decreaseHitPoints(damage_points);
        
        // In addition to the regular hit point damage magic fangs of sleep do when the attacker hits the defender, there is a 1 in 5 chance that the magic fangs of sleep will put the defender to sleep. The number of moves the sleep will last (the sleep time) is a random integer from 2 to 6, call it X. If the defender is already asleep, with current sleep time Y, then the defender's sleep time becomes the maximum of X and Y (and not, say, Y+X).
        if (monster->returnWP()->getName() == "magic fangs of sleep"){
            // 1 in 5 chance
            bool prob = trueWithProbability(0.2);
            if (prob == true){
                int new_sleep_time = randInt(2,6);
                int old_sleep_time = m_player->getSleepTime();
                // new_sleep_time is greater
                if (new_sleep_time > old_sleep_time){
                    // set players sleep time
                    m_player->setSleepTime(new_sleep_time);
                }
                // // we have a succesful attack and player has been slept
                m_messages.push_back("the " + monster->get_name() + " " + monster->returnWP()->getAction() + " Player and hits, putting Player to sleep.");
            }
            else{
                // we have a succesful attack and player has not been slept (check if magic fangs killed the player
                if (m_player->getHitPoints() <= 0){
                    m_messages.push_back("the " + monster->get_name() + " " + monster->returnWP()->getAction() + " Player dealing a final blow.");
                }
                else{
                    m_messages.push_back("the " + monster->get_name() + " " + monster->returnWP()->getAction() + " Player and hits.");
                }
             }
        }
        else{
            // we have a succesful attack
            // player has been killed
            if (m_player->getHitPoints() <= 0){
                m_messages.push_back("the " + monster->get_name() + " " + monster->returnWP()->getAction() + " Player dealing a final blow.");
            }
            else{
                m_messages.push_back("the " + monster->get_name() + " " + monster->returnWP()->getAction() + " Player and hits.");
            }
        }
    }
    else{
        // player did not hit the monster
        m_messages.push_back("the " + monster->get_name() + " " + monster->returnWP()->getAction() + " Player and misses.");
    }
}

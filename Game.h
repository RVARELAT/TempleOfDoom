//
//  Game.h
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/12/24.
//
// Game.h
#ifndef GAME_INCLUDED
#define GAME_INCLUDED
// You may add data members and other member functions to this class.
#include "Actors.h"
class Maze;
class Game{
public:
    // constructor
    Game(int goblinSmellDistance);
    // destructor
    virtual ~Game();
    // play the game
    void play();
private:
    Maze *m_maze;
};
#endif // GAME_INCLUDED


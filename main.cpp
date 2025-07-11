//
//  main.cpp
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/12/24.
//

// main.cpp

// Note:  YOU MUST NOT MAKE ANY CHANGE TO THIS FILE, except for the argument
// to the Game constructor.

#include "Game.h"

int main()
{
      // Your program must use whatever value is passed to the Game constructor
      // as the distance a goblin can smell.  The spec stated this is 15.  Some
      // people might implement the recursive goblin algorithm for determining
      // the shortest path to the player in a way that takes an uncomfortably
      // long time for that distance.  If you're one of them, then until you
      // improve your algorithm, pass a value smaller than 15 to the game
      // constructor so your game is comfortable to play.
//
    Game g(10);
    g.play();

}

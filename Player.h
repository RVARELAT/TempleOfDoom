//
//  Player.h
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/12/24.
//

#ifndef Player_h
#define Player_h

class Player{
public:
    // Constructor to initialize player's position
    Player(int startX, int startY);
    
    // member functions
    
    // move the player in a specified direction
    void move(char direction);
    // decrease player's health
    void decrease_health(int amount);
    // check if the player is alive
    bool is_alive() const;
    
    // getters and setters
    
    // set player's position
    void set_position(int x, int y);
    // get player's position
    void get_position(int& x, int& y) const;
    // get player's health
    int get_health() const;
    
private:
    // Player's x-coordinate
    int m_x;
    // Player's y-coordinate
    int m_y;
    // Player's health
    int m_health; // Player's health
};


#endif /* Player_h */

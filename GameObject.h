//
//  GameObject.h
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/19/24.
//
#ifndef GameObject_h
#define GameObject_h
#include <string>
//Since weapons, scrolls, and the golden idol share some characteristics (e.g., they can be picked up, they can occupy the same space as an actor, etc.), let's classify them as game objects. Each game object has a name (e.g. "long sword").
class GameObject {
public:
    // Constructor
    GameObject(std::string name, int row, int col, char symbol);
    // destructor to ensure proper cleanup of derived classes
    virtual ~GameObject();
    // getters
    std::string getName() const;
    int get_row() const;
    int get_col() const;
    char get_symbol();
private:
    // object name
    std::string m_name;
    // object position
    int m_row;
    int m_col;
    // object symbol
    char m_symbol;
};
#endif /* GameObject_h */

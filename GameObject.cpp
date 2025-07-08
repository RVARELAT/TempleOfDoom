//
//  GameObject.cpp
//  CS32_PROJECT3
//
//  Created by Ricardo Varela Tellez on 5/19/24.
//
#include <stdio.h>
#include "GameObject.h"
// Constructor implementation
GameObject::GameObject(std::string name, int row, int col, char symbol){
    m_name = name;
    m_row = row;
    m_col = col;
    m_symbol = symbol;
}
// destructor
GameObject::~GameObject(){
    
}

char GameObject::get_symbol(){
    return m_symbol;
}

std::string GameObject::getName() const {
    return m_name;
}

int GameObject::get_row() const {
    return m_row;
}

int GameObject::get_col() const {
    return m_col;
}


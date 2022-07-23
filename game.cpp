#include "game.h"
#include "enemy.h"
#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>     //include all necessary external files



Game::Game()            //constructor
{
    std::cout << "Game Konstruktor" << std::endl;
}

Game::~Game()           //destructor
{
    std::cout << "Game Dekonstruktor" << std::endl;
    // delete all objects
    delete Fieldg.field;
}

Field Game::getField()  //?
{
    return Fieldg;
}


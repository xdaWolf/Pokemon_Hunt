#include "game.h"
#include "enemy.h"
#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

//Constructor / Destructor

Game::Game()
{
    std::cout << "Game Konstruktor" << std::endl;

}

Game::~Game()
{
    std::cout << "Game Dekonstruktor" << std::endl;
    // delete all objects
    delete Fieldg.field;
}

Field Game::getField()
{
    return Fieldg;
}


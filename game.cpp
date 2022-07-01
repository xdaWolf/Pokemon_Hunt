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
    delete this->Fieldg.field;
}

//private functions

sf::RenderWindow* Game::getGameField()
{
    return this->Fieldg.field;
}

Field Game::getField()
{
    return this->Fieldg;
}

Game Game::getGame()
{
    return *this;
}

int Game::random(int min, int max)
{
    srand(time(0));
    rand();
    rand();
    rand();
    return rand() % max + min;
}


// public functions




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
/*/
Enemy Game::getEnemy1()	
{
    return this->enemy1;
}

Enemy Game::getEnemy2()	
{
    return this->enemy2;
}

Enemy Game::getEnemy3()	
{
    return this->enemy3;
}
/*/
Game Game::getGame()
{
    return *this;
}


// public functions




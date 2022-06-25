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
    //this->initField();
    //this->initVariables();
    //this->initEnemies();

}

Game::~Game()
{
    std::cout << "Game Dekonstruktor" << std::endl;
    // delete all objects
    delete this->Fieldg.field;
}

//private functions

void Game::initVariables()
{
    // init variables
    this->Fieldg.field = nullptr;
    std::cout << "InitVar" << std::endl;

}

void Game::initField()
{
    Fieldg = Field();
    std::cout << "InitField" << std::endl;
}

void Game::initEnemies()
{
    this->enemy1 = Enemy();
    this->enemy2 = Enemy();
    this->enemy3 = Enemy();

}

sf::RenderWindow* Game::getGameField()
{
    return this->Fieldg.field;
}

Field Game::getField()
{
    return this->Fieldg;
}

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

Game Game::getGame()
{
    return *this;
}


// public functions




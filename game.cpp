#include "game.h"
#include "enemy.h"
#include "field.h"

//private functions

void Game::initVariables()
{
    // init variables
    this->fieldg.field = nullptr;

}

void Game::initField()
{
    fieldg = Field();
}

void Game::initEnemies()
{
    this->enemy1 = Enemy();
    this->enemy2 = Enemy();
    this->enemy3 = Enemy();

}

//Constructor / Destructor

Game::Game()
{
    this->initVariables();
    this->initField();
    this->initEnemies();

}

Game::~Game()
{
    // delete all objects
    delete this->fieldg.field;
}

sf::RenderWindow* Game::getGameField()
{
    return this->fieldg.field;
}

Field Game::getField()
{
    return this->fieldg;
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




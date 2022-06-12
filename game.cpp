#include "game.h"

//private functions

void Game::initVariables()
{
    // init variables
    this->window = nullptr;

}

void Game::initWindow()
{
    this->window = new Window();
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
    this->initWindow();
    this->initEnemies();
    this->window->pollEvents();
    this->window->update();
    this->window->render();
}

Game::~Game()
{
    this->window->~Window();
}


// public functions




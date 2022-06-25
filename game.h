#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "enemy.h"
#include "field.h"

#ifndef GAME_H_
#define GAME_H_

/*
    Class that manages all the data of the game
*/


class Game
{
    private:
    // variables
    Enemy enemy1, enemy2, enemy3;
    Field Fieldg;
    //Game objects
    

    //functions
    void initVariables();
    void initField();
    void initEnemies();

    public:
    // Constructor / Destructor
    Game();
    ~Game();

    //Variables
    sf::RenderWindow* getGameField();
    Field getField();
    Enemy getEnemy1();
    Enemy getEnemy2();
    Enemy getEnemy3();
    Game getGame();
};

#endif



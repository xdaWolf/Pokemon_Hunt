#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "enemy.cpp"
#include "field.cpp"

#ifndef GAME_H_
#define GAME_H_

/*
    Class that manages all the data of the game
*/

class Game
{
    private:
    // variables

    //Game objects
    Enemy enemy1, enemy2, enemy3;
    Field field;



    //functions
    void initVariables();
    void initWindow();
    void initEnemies();

    public:
    // Constructor / Destructor
        Game();
        ~Game();

    //Variables
    
};

#endif



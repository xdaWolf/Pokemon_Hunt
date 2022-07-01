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
    Field Fieldg;
    //Game objects
    

    //functions

    public:
    // Constructor / Destructor
    Game();
    ~Game();

    //Variables
    sf::RenderWindow* getGameField();
    Field getField();
    Game getGame();
};

#endif


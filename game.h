#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#ifndef GAME_H_
#define GAME_H_

/*
    Class that manages all the data of the game
*/

class Game
{
    private:
    // variables
    sf::RenderWindow* window;
    sf::Event event;

    //functions
    void initVariables();
    void initWindow();

    public:
    // Constructor / Destructor
        Game();
        ~Game();

    //Variables
    const bool getWindowIsOpen() const;

    // functions
    void pollEvents();
    void update(); // update the game data
    void render();
    
};

#endif



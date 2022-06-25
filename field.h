#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

//#include "game.h"

#ifndef FIELD_H_
#define FIELD_H_


/*
    Class that is used to create the gamefield
*/

class Field
{
    
    private:

    // variables
    

    public:

    //variables
    sf::RenderWindow* field;
    sf::Event event;
    sf::Sprite spritef;
    sf::Texture texturef;
    //class Game game;

    //Constructors / Destructors
    Field();
    ~Field();

    //Functions
    void pollEvents();
    void update(); // update the game data
    void render();

    const bool getFieldIsOpen() const;

};

#endif

#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "enemy.h"
#include "player.h"
#include "collectable.h"

#ifndef FIELD_H_
#define FIELD_H_


/*
    Class that is used to create the gamefield
*/

class Field
{
    
    private:
    // variables
    Collectable collectables[3];
    Enemy enemies[6];
    Player player;

    sf::Sprite spritePD;
    sf::Texture texturePD;
    
    sf::Sprite spriteHP;
    sf::Texture textureHP;

    sf::Event event;
    sf::Sprite spritef;
    sf::Texture texturef;

    void checkCollision();
    void updateHealth();
    void checkPositions();

    public:

    //variables
    sf::RenderWindow* field;

    //Constructors / Destructors
    Field();
    ~Field();

    //public Functions
    void pollEvents();
    void update(); // update the game data
    void render();
    //GET
    const bool getFieldIsOpen() const;

};

#endif

#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


#ifndef ENEMY_H_
#define ENEMY_H_

/*
    Enemy-Class: Create Enemy-Objects that are visualized on the field
*/

class Enemy
{
    private:
    // variables
    sf::RectangleShape shape;
    sf::Texture texturee;
    sf::Sprite spritee;

    //Field field;

    // functions


    public:
    // Constructor / Destructor
        Enemy();
        ~Enemy();

    sf::Sprite getSprite();


};

#endif
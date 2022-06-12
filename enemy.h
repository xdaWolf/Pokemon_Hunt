#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "field.cpp"

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
    sf::Texture texture;

    //Field field;

    // functions


    public:
    // Constructor / Destructor
        Enemy();
        ~Enemy();


};

#endif
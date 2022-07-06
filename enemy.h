#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


#ifndef ENEMY_H_
#define ENEMY_H_

/*
    Enemy-Class: Create Enemy-Objects that are visualized on the field and once the player hits the enemy, he loses one hp
*/

class Enemy
{
    private:
    // variables
    //sf::RectangleShape shapeE;
    sf::Texture textureE;
    //sf::Sprite spriteE;



    public:
    // Constructor / Destructor
    Enemy();
    ~Enemy();

    sf::RectangleShape shapeE;

    //public functions
    //GET
    sf::Sprite getSprite();
    int giveRandomNumber(int pMin, int pMax);
    sf::Sprite spriteE;


};

#endif
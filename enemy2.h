#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


#ifndef ENEMY2_H_
#define ENEMY2_H_

/*
    Enemy2-Class: Create Enemy2-Objects that are visualized on the field and once the player gets hit by the enemy(Pokeball), he loses one hp
*/

class Enemy2
{
    private:
    // variables
    //sf::RectangleShape shapeE;
    sf::Texture textureE2;
    //sf::Sprite spriteE;



    public:
    // Constructor / Destructor
    Enemy2();
    ~Enemy2();

    sf::RectangleShape shapeE2;

    //public functions
    //GET
    sf::Sprite getSprite();
    int giveRandomNumber(int pMin, int pMax);
    sf::Sprite spriteE2;


};

#endif
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
    //VARIABLES
    sf::Texture textureE2;

    public:

    Enemy2();           //constructor
    ~Enemy2();          //destructor
    
    //VARIABLES
    double speed;
    
    //VISUALS
    sf::Sprite spriteE2;

    //METHODS
    double fRand(double fMin, double fMax);
    int giveRandomNumber(int pMin, int pMax);
};

#endif
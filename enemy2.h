#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>    //include all necessary external files


#ifndef ENEMY2_H_
#define ENEMY2_H_

/*
    Enemy2 class: create enemy2 objects that are visualized on the field. Once hit by the enemy (Pokeball), the player loses 1 HP.
*/

class Enemy2
{
    private:
    //PRIVATE VISUALS
    sf::Texture textureE2;  //texture of enemy2


    public:
    Enemy2();               //constructor
    ~Enemy2();              //destructor
    
    //PUBLIC VARIABLES
    double speed;           //speed of Pokeballs
    
    //PUBLIC VISUALS
    sf::Sprite spriteE2;    //sprite of enemy2

    //PUBLIC METHODS
    double fRand(double fMin, double fMax);     //randomization of Pokeball speed
    int giveRandomNumber(int pMin, int pMax);   //randomization of Pokeball spawn height
    
};

#endif
#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>    //include all necessary external files


#ifndef ENEMY_H_
#define ENEMY_H_

/*
    Enemy class: Create enemy objects that are visualized on the field. Once hit by the enemy (Trainer), the player loses 1 HP.
*/

class Enemy
{
    private:
    //VARIABLES
    sf::Texture textureE;   //texture of trainer


    public:
    Enemy();                //constructor
    ~Enemy();               //destructor

    //VISUALS
    sf::Sprite spriteE;     //sprite of trainer

    //GET
    int giveRandomNumber(int pMin, int pMax);   //randomization of Trainer spawn location

};

#endif
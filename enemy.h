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
    //VARIABLES
    sf::Texture textureE;

    public:

    Enemy();        //constructor
    ~Enemy();       //destructor

    //VISUALS
    sf::Sprite spriteE;

    //GET
    int giveRandomNumber(int pMin, int pMax);

};

#endif
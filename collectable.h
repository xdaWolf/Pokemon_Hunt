#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

/*
    Collectable-Class: Used to create Collectables, which are collected by the player to win the game
*/

class Collectable
{
    private:
    //VARIABLES
    sf::Texture textureC;

    public:

    Collectable();          //constructor
    ~Collectable();         //destructor
    
    //VISUALS
    sf::Sprite spriteC;     

    //METHODS
    int giveRandomNumber(int pMin, int pMax);

};

#endif
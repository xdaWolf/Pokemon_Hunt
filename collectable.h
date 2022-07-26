#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

/*
    Collectable-Class: Used to create 3 Collectables, which are collected by the player to win the game
*/

class Collectable
{
    private:
    //Variables
    //sf::RectangleShape shapeC;
    sf::Texture textureC;
    //sf::Sprite spriteC;

    public:
    //Constructor / Destructor
    Collectable();
    ~Collectable();
    //public functions
    sf::Sprite getSprite();
    int giveRandomNumber(int pMin, int pMax);
    sf::Sprite spriteC;
    int collected;

};

#endif
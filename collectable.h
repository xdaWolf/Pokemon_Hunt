#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>    //include all necessary external files


#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

/*
    Collectable class: create collectable objects that are visualized on the field. Once collected by the player, the collectables (Pokemon) appear on the "collected Pokemon" textbox.
*/

class Collectable
{
    private:
    //VARIABLES
    sf::Texture textureC;   //texture of Pokemon

    public:

    Collectable();          //constructor
    ~Collectable();         //destructor
    
    //VISUALS
    sf::Sprite spriteC;     //sprite of Pokemon

    //METHODS
    int giveRandomNumber(int pMin, int pMax);   //randomization of Pokemon spawn location

};

#endif
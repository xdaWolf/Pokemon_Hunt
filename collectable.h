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
<<<<<<< Updated upstream
    //Variables
    sf::RectangleShape shapeC;
    sf::Texture textureC;
    sf::Sprite spriteC;

    public:
    //Constructor / Destructor
    Collectable();
    ~Collectable();
    //public functions
    sf::Sprite getSprite();
=======
    //VARIABLES
    sf::Texture textureC;   //texture of Pokemon

    public:

    Collectable();          //constructor
    ~Collectable();         //destructor
    
    //VISUALS
    sf::Sprite spriteC;     //sprite of Pokemon

    //METHODS
    int giveRandomNumber(int pMin, int pMax);   //randomization of Pokemon spawn location
>>>>>>> Stashed changes

};

#endif
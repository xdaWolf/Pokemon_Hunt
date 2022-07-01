#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


#ifndef PLAYER_H_
#define PLAYER_H_

/*
    Player-Class: Create Player-Objects that are visualized on the field
*/

class Player
{
    private:
    // variables
    sf::RectangleShape shapeP;
    sf::Texture textureP;
    sf::Vector2f shapePPos;

    int speed;

    //Field field;

    // functions


    public:
    // Constructor / Destructor
    Player();
    ~Player();
    sf::Sprite spriteP;
    sf::Sprite getSprite();
    sf::Vector2f getShapePPos();
    sf::RectangleShape getShape();
    //void setSprite();


};

#endif
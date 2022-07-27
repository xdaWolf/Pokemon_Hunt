#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>


#ifndef PLAYER_H_
#define PLAYER_H_

/*
    Player-Class: Create Player-Objects that are visualized on the field
*/

class Player
{
    private:
    //Variables
    //sf::RectangleShape shapeP;
    //sf::Texture textureP;
    sf::Vector2f shapePPos;
    int hp;
    int speed;
    int collected;

    public:
    // Constructor / Destructor
    Player();
    ~Player();

    //public variables
    sf::Texture textureP; //this do be public now cuz field yea
    sf::RectangleShape shapeP;
    sf::Sprite spriteP;
    int spawnPX, spawnPY;
    //int spawnzoneWidth;
    //int spawnzoneHeight;
    //public functions
    //GET
    int getHealthPoints();
    int getCollected();
    int getSpeed();
    int getSpawnzone();

    //SET
    void setTexture(const std::string& pTexture);
    void setHealthPoints(int pHP);
    void setCollected(int pCollected);

};

#endif
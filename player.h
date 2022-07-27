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
    //VARIABLES
    int hp = 3;             //player has 3 health-points
    int speed = 9;          //speed of player, HAS TO BE ODD NUMBER IN ORDER FOR ANIMATIONS TO WORK PROPERLY
    int collected = 0;          //counts how many collectables were collected
    int spawnPX = 550;                  //horizontal spawn point of player
    int spawnPY = 200;                  //vertical spawn point of player

    //VISUALS
    sf::Texture textureP;           //texture of player

    public:

    Player();           //Constructor
    ~Player();          //Destructor

    //VISUALS
    sf::Sprite spriteP;         //sprite of Player, is used a lot in field
    sf::RectangleShape shapeP;      //used in field to show that damage was taken
    
    //METHODS
    //Get-Methods
    int getHealthPoints();          //returns health-points
    int getCollected();             //returns amount of currently collected collectables
    int getSpeed();                 //returns speed of player
    //Set-Methods
    void setTexture(const std::string& pTexture);       //used to change texture of player(shows, which direction player is moving)
    void setHealthPoints(int pHP);          //updates health-points
    void setCollected(int pCollected);      //updates collected collectables
};

#endif
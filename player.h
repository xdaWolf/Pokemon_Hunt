#pragma once

#include "BaseEntity.h"

#ifndef PLAYER_H_
#define PLAYER_H_

/*
    Player class: create player objects that are visualized on the field
*/

class Player : public BaseEntity
{
private:
    // PRIAVTE VARIABLES
    int hp = 3;        // player has 3 health-points
    int speed = 9;     // speed of player, IMPORTANT: this has to be an odd number in order for the player animation to work properly
    int collected = 0; // counts how many collectables were collected

    // PRIVATE VISUALS
    // sf::Texture textureP; // texture of player

public:
    Player();  // Constructor
    ~Player(); // Destructor

    // PUBLIC VARIABLES
    int spawnPX = 550; // horizontal spawn point of player
    int spawnPY = 200; // vertical spawn point of player

    // PUBLIC VISUALS
    // sf::Sprite spriteP;        // sprite of player
    sf::RectangleShape shapeP; // shape  of player, used in to show damage animation

    // PUBLIC METHODS
    // Get-Methods
    int getHealthPoints(); // returns health-points
    int getCollected();    // returns amount of currently collected collectables
    int getSpeed();        // returns speed of player
    // Set-Methods
    void setTexture(const std::string &pTexture); // change texture of player (used for walking animation / which direction the player is moving)
    void setHealthPoints(int pHP);                // updates health-points
    void setCollected(int pCollected);            // updates collected collectables

    void initializeSpriteAndTexture() override; // initialize sprite and texture
};

#endif
#pragma once

#include "BaseEntity.h"
#include "Observer.h"

#ifndef PLAYER_H_
#define PLAYER_H_

/*
    Player class: create player object that are visualized on the field
*/

class Player : public BaseEntity, public Observer
{
private:
    // VARIABLES
    int hp = 3;        // player has 3 health-points
    int speed = 9;     // speed of player, IMPORTANT: this has to be an odd number in order for the player animation to work properly
    int collected = 0; // counts how many collectables were collected

public:
    // VARIABLES
    int spawnPX = 550;         // horizontal spawn point of player
    int spawnPY = 200;         // vertical spawn point of player
    sf::RectangleShape shapeP; // shape  of player, used in to show damage animation

    // METHODS
    Player();  // Constructor
    ~Player(); // Destructor

    int getHealthPoints();                        // returns health-points
    int getCollected();                           // returns amount of currently collected collectables
    int getSpeed();                               // returns speed of player
    void setTexture(const std::string &pTexture); // change texture of player (used for walking animation / which direction the player is moving)
    void setHealthPoints(int pHP);                // updates health-points
    void initializeSpriteAndTexture() override;   // initialize sprite and texture

    void refresh(int pHealth, int pSpeed, int pCollected) override;
};

#endif
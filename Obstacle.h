#pragma once

#include "BaseEntity.h"

#ifndef OBSTACLE_H_
#define OBSTACLE_H_
using namespace sf;
/*
    Obstacle class:
*/

class Obstacle : public BaseEntity
{
private:
    // VARIABLES

public:
    // METHODS

    Obstacle();  // constructor
    ~Obstacle(); // destructor

    void initializeSpriteAndTexture() override; // initializes sprite and texture
};

#endif
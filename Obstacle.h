#pragma once

#include "BaseEntity.h"

#ifndef OBSTACLE_H_
#define OBSTACLE_H_
using namespace sf;
/*
    Obstacle class: create obstacles that are visualized on the field. The player has to move around them.
*/

class Obstacle : public BaseEntity
{
private:
public:
    // METHODS
    Obstacle();  // constructor
    ~Obstacle(); // destructor

    void initializeSpriteAndTexture() override;
};

#endif
#pragma once

#include "BaseEntity.h"

#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_
using namespace sf;
/*
    HealthBar class: Class for the health bar of the player, health bar is on the top right of the screen
*/

class HealthBar : public BaseEntity
{
private:
    // VARIABLES

public:
    // METHODS
    HealthBar();  // constructor
    ~HealthBar(); // destructor

    void initializeSpriteAndTexture() override;
};

#endif
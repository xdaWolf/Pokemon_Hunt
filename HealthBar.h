#pragma once

#include "BaseEntity.h"

#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_
using namespace sf;
/*
    HealthBar class:
*/

class HealthBar : public BaseEntity
{
private:
    // VARIABLES

public:
    // METHODS
    HealthBar();  // constructor
    ~HealthBar(); // destructor

    void initializeSpriteAndTexture() override; // initialize sprite and texture
};

#endif
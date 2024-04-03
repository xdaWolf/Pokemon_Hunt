#pragma once

#include "BaseEntity.h"

#ifndef POKECENTER_H_
#define POKECENTER_H_
using namespace sf;
/*
    PokeCenter class:
*/

class PokeCenter : public BaseEntity
{
private:
    // VARIABLES

public:
    // METHODS
    PokeCenter();  // constructor
    ~PokeCenter(); // destructor

    void initializeSpriteAndTexture() override; // initialize sprite and texture
};

#endif
#pragma once

#include "BaseEntity.h"

#ifndef POKEBOX_H_
#define POKEBOX_H_
using namespace sf;
/*
    PokeBox class:
*/

class PokeBox : public BaseEntity
{
private:
    // VARIABLES

public:
    // METHODS
    PokeBox();  // constructor
    ~PokeBox(); // destructor

    void initializeSpriteAndTexture() override; // initialize sprite and texture
};

#endif
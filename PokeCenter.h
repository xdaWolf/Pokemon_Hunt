#pragma once

#include "BaseEntity.h"

#ifndef POKECENTER_H_
#define POKECENTER_H_
using namespace sf;
/*
    PokeCenter class: player needs to go with all collectables to the PokeCenter to win the game
*/

class PokeCenter : public BaseEntity
{
private:
public:
    // METHODS
    PokeCenter();  // constructor
    ~PokeCenter(); // destructor

    void initializeSpriteAndTexture() override; // initialize sprite and texture
};

#endif
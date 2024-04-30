#pragma once

#include "BaseEntity.h"

#ifndef POKEBOX_H_
#define POKEBOX_H_
using namespace sf;
/*
    PokeBox class: sprite that is displayed at the bottom left corner of the screen, collected pokemons are displayed in the pokebox
*/

class PokeBox : public BaseEntity
{
private:
public:
    // METHODS
    PokeBox();  // constructor
    ~PokeBox(); // destructor

    void initializeSpriteAndTexture() override;
};

#endif
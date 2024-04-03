#pragma once

#include "BaseEntity.h"

#ifndef POKEBALL_H_
#define POKEBALL_H_
using namespace sf;
/*
    Pokeball class:
*/

class Pokeball : public BaseEntity
{
private:
    // VARIABLES

public:
    // METHODS
    Pokeball();  // constructor
    ~Pokeball(); // destructor

    double speed; // speed of pokeball

    void initializeSpriteAndTexture() override;
    int giveRandomNumber(int pMin, int pMax) override;
};

#endif
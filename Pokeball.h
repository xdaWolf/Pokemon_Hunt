#pragma once

#include "BaseEntity.h"

#ifndef POKEBALL_H_
#define POKEBALL_H_
using namespace sf;
/*
    Pokeball class: create pokeball objects that are visualized on the field. The player has to avoid them.
*/

class Pokeball : public BaseEntity
{
private:
public:
    // VARIABLES
    double speed; // speed of pokeball

    // METHODS
    Pokeball();  // constructor
    ~Pokeball(); // destructor

    void initializeSpriteAndTexture() override;
    int giveRandomNumber(int pMin, int pMax) override;
    int giveRandomNumberWithoutSpawnProof(int pMin, int pMax);
};

#endif
#pragma once

#include "BaseEntity.h"

#ifndef TRAINER_H_
#define TRAINER_H_
using namespace sf;
/*
    Trainer class: objects on the screen, if player collides, damage is dealt
*/

class Trainer : public BaseEntity
{
private:
public:
    // METHODS
    Trainer();  // constructor
    ~Trainer(); // destructor
};

#endif
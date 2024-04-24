#pragma once

#include "Field.h"

#ifndef NORMALGAMEMODE_H_
#define NORMALGAMEMODE_H_
using namespace sf;
/*
    NormalGameMode class: Defines Methods with rules and actions for the normal game mode.
*/

class NormalGameMode
{
private:
    // VARIABLES
    Field *field;

public:
    // METHODS
    NormalGameMode(Field *pField); // constructor
    ~NormalGameMode();             // destructor

    void update();
    void render();

    void pokeballMovement();
};

#endif
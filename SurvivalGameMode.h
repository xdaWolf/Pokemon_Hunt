#pragma once

#include "Field.h"

#ifndef SURVIVALGAMEMODE_H_
#define SURVIVALGAMEMODE_H_
using namespace sf;
/*
    SurvivalGameMode class: Defines Methods with rules and actions for the survival game mode.
*/

class SurvivalGameMode
{
private:
    // VARIABLES
    Field *field;

public:
    // METHODS
    SurvivalGameMode(Field *pField); // constructor
    ~SurvivalGameMode();             // destructor

    void update();
    void render();

    void pokeballMovement();
    void resetGame();
};

#endif
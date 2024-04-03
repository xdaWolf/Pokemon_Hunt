#pragma once

#include "BaseEntity.h"

#ifndef MENU_H_
#define MENU_H_
using namespace sf;
/*
    Menu class:
*/

class Menu : public BaseEntity
{
private:
    // VARIABLES

public:
    // METHODS
    Menu();  // constructor
    ~Menu(); // destructor

    void initializeSpriteAndTexture() override; // initializes sprite and texture
};

#endif
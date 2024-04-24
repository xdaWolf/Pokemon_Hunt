#pragma once

#include "BaseEntity.h"

#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

using namespace sf;
/*
    Collectable class: create collectable objects that are visualized on the field. Once collected by the player, the collectables (Pokemon) appear on the "collected Pokemon" textbox.
*/

class Collectable : public BaseEntity
{
private:
public:
    Collectable();  // constructor
    ~Collectable(); // destructor
};

#endif
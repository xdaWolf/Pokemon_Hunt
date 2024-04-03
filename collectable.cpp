#include "Collectable.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

Collectable::Collectable() : BaseEntity() // constructor
{
    std::cout << "Collectable constructor" << std::endl;
    setTexture("resources/collectable_" + std::to_string(giveRandomNumber(1, 6)) + ".png"); // select random Pokemon image
    initializeSpriteAndTexture();                                                           // set spawn point and configure sprinte and texture
}

Collectable::~Collectable(){}; // destructor
#include "Trainer.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

Trainer::Trainer() : BaseEntity() // constructor
{
    std::cout << "Trainer constructor" << std::endl;
    setTexture("resources/enemy_" + std::to_string(giveRandomNumber(1, 6)) + ".png");
    initializeSpriteAndTexture();
}

Trainer::~Trainer() // destructor
{
}

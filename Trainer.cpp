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

/*/
std::cout << "Enemy constructor" << std::endl;
    textureE.loadFromFile("resources/enemy_" + std::to_string(giveRandomNumber(1, 6)) + ".png"); // select random trainer image
    textureE.setSmooth(true);
    spriteE.setTexture(textureE); // set texture of "sprite" to trainer image
    int positionX, positionY;
    positionX = giveRandomNumber(0, 1920);     // select random horizontal spawn point
    positionY = giveRandomNumber(0, 900);      // select random vertical spawn point
    spriteE.setPosition(positionX, positionY); // set sprite at spawn point

/*/

Trainer::~Trainer() {} // destructor

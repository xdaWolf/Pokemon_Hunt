#include "Pokeball.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

Pokeball::Pokeball() : BaseEntity() // constructor
{
    std::cout << "Pokeball constructor" << std::endl;
    setTexture("resources/pokeball_" + std::to_string(giveRandomNumber(1, 5)) + ".png");
    initializeSpriteAndTexture();
}

Pokeball::~Pokeball() {} // destructor

void Pokeball::initializeSpriteAndTexture()
{
    this->speed = giveRandomDouble(7.5, 9.5); // select random speed for Pokeball
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    int positionX, positionY;
    positionX = 1970;                               // select random horizontal spawn point
    positionY = giveRandomNumber(0, 900);           // select random vertical spawn point
    this->sprite.setPosition(positionX, positionY); // set "sprite" at spawn point
}

int Pokeball::giveRandomNumber(int pMin, int pMax)
{
    auto start = std::chrono::steady_clock::now();
    int dfe = 100; // distance from edges (in pixels, implementation idea: automatic number using size of respective sprite)
    Sleep(10);
    auto end = std::chrono::steady_clock::now();
    int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // get a pseudo-random number by counting the microseconds it took the program to process the lines above

    if (pMax < 100) // allows up to 99 different sprites for enemies, requirement: window size is 100x100px or larger
    {
        return microseconds % pMax + pMin; // select random sprite
    }
    else
    {
        int spawnheight = microseconds % (pMax - 2 * dfe) + dfe; // select random position for enemy to spawn (considering the set distance from edges)
        if (spawnheight > 58 && spawnheight <= 160)              // in case the pokeball tries to spawn within the player's vertical spawn position (upper half)
        {
            return 58; // have it spawn right above the player instead (number to return = player y spawn - Pokeball y size - player y size/2)
        }
        else if (spawnheight >= 161 && spawnheight < 263) // in case the pokeball tries to spawn within the player's vertical spawn position (lower half)
        {
            return 263; // have it spawn right below the player instead (number to return = player y spawn + player y size - player y size/2)
        }
        else
        {
            return spawnheight; // otherwise keep the random spawn height
        }
    }
}

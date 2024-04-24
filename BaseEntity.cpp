#include "BaseEntity.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

BaseEntity::BaseEntity() // constructor
{
    std::cout << "BaseEntity constructor" << std::endl;
}

BaseEntity::~BaseEntity() {} // destructor

void BaseEntity::setTexture(const std::string &pTexturePath)
{
    if (!texture.loadFromFile(pTexturePath))
    {
        std::cerr << "Error loading texture: " << pTexturePath << std::endl;
    }
    sprite.setTexture(texture);
}

const Texture *BaseEntity::getTexture() const
{
    return &texture;
}

void BaseEntity::initializeSpriteAndTexture()
{
    texture.setSmooth(true);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
    int positionX, positionY;
    positionX = giveRandomNumber(0, 1920);    // select random horizontal spawn point
    positionY = giveRandomNumber(0, 900);     // select random vertical spawn point
    sprite.setPosition(positionX, positionY); // set sprite at spawn point
}

int BaseEntity::giveRandomNumber(int pMin, int pMax)
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
        return microseconds % (pMax - 2 * dfe) + dfe; // select random position for enemy to spawn (considering the set distance from edges)
    }
}

double BaseEntity::giveRandomDouble(double pMin, double pMax)
{
    double random = (double)rand() / RAND_MAX; // random number between 0 and 1
    return pMin + random * (pMax - pMin);      // number converted to be between lowest and highest possible speed
}
#include "Obstacle.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

Obstacle::Obstacle() : BaseEntity() // constructor
{
    std::cout << "Obstacle constructor" << std::endl;
}

void Obstacle::initializeSpriteAndTexture()
{
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    sprite.setPosition(this->giveRandomNumber(0, 1920), this->giveRandomNumber(0, 900));                      // place health bar sprite in the top right of the screen
    sprite.setOrigin(sf::Vector2f(this->getTexture()->getSize().x / 2, this->getTexture()->getSize().y / 2)); // move origin of sprite (default: top left) to center of sprite
}

Obstacle::~Obstacle() {} // destructor
#include "HealthBar.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

HealthBar::HealthBar() : BaseEntity() // constructor
{
    std::cout << "HealthBar constructor" << std::endl;
    setTexture("resources/health_bar_3.png"); // at the beginning of the game player always has 3 health points
    initializeSpriteAndTexture();
}

void HealthBar::initializeSpriteAndTexture() // override to set sprite to fixed position on screen
{
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    sprite.setPosition(1600, 50);                                                                             // place health bar sprite in the top right of the screen
    sprite.setOrigin(sf::Vector2f(this->getTexture()->getSize().x / 2, this->getTexture()->getSize().y / 2)); // move origin of sprite (default: top left) to center of sprite
}

HealthBar::~HealthBar() {} // destructor

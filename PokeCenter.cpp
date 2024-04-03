#include "PokeCenter.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

PokeCenter::PokeCenter() : BaseEntity() // constructor
{
    std::cout << "PokeCenter constructor" << std::endl;
    setTexture("resources/pokecenter.png");
    initializeSpriteAndTexture();
}

PokeCenter::~PokeCenter() {} // destructor

void PokeCenter::initializeSpriteAndTexture()
{
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    sprite.setPosition(1800, 500);                                                                            // place Pokecenter sprite on the right of the screen
    sprite.setOrigin(sf::Vector2f(this->getTexture()->getSize().x / 2, this->getTexture()->getSize().y / 2)); // move origin of sprite (default: top left) to center of sprite
}

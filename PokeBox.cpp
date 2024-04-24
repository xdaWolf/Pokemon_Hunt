#include "PokeBox.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

PokeBox::PokeBox() : BaseEntity() // constructor
{
    std::cout << "PokeBox constructor" << std::endl;
    setTexture("resources/collected_pokemon.png");
    initializeSpriteAndTexture();
}

void PokeBox::initializeSpriteAndTexture()
{
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    sprite.setPosition(250, 1000);                                                                            // place pokebox sprite in the bottom left of the screen
    sprite.setOrigin(sf::Vector2f(this->getTexture()->getSize().x / 2, this->getTexture()->getSize().y / 2)); // move origin of sprite (default: top left) to center of sprite
}

PokeBox::~PokeBox() {} // destructor

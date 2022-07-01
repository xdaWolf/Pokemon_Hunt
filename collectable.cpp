#include "collectable.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <experimental/random>

Collectable::Collectable()
{

    std::cout << "Collectable Konstruktor" << std::endl;
    std::cout << "Rand:" + std::to_string(std::experimental::randint(1,6)) << std::endl;
    //SET VARIABLES - COLLECTABLE
    this->textureC.loadFromFile("resources/collectable_" + std::to_string(std::experimental::randint(1,6)) + ".png");
    this->textureC.setSmooth(true);
    this->shapeC.setTexture(&textureC);
    this->shapeC.setSize(sf::Vector2f(this->textureC.getSize().x, this->textureC.getSize().y));
    this->spriteC.setTexture(textureC);
    this->shapeC.setPosition(std::experimental::randint(0,1000),std::experimental::randint(0,600));
    this->spriteC.setPosition(std::experimental::randint(0,1000),std::experimental::randint(0,600));

};

Collectable::~Collectable()
{

};

sf::Sprite Collectable::getSprite()
{
    return this->spriteC;

}
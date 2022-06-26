#include "player.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <experimental/random>
//Constructor / Destructor

Player::Player()
{
    this->speed = 10;
    this->shapePPos = sf::Vector2f(std::experimental::randint(0,1000),std::experimental::randint(0,600));
    std::cout << "Player Konstruktor" << std::endl;
    this->textureP.loadFromFile("resources/pikachu_forward_1.png");
    this->textureP.setSmooth(true);
    this->shapeP.setTexture(&textureP);
    this->shapeP.setSize(sf::Vector2f(this->textureP.getSize().x, this->textureP.getSize().y));
    this->spriteP.setTexture(textureP);
    this->shapeP.setPosition(shapePPos);
    this->spriteP.setPosition(shapePPos);
    

};

Player::~Player()
{

    //delete this->field;
};


sf::Sprite Player::getSprite()
{
    return this->spriteP;
}

sf::Vector2f Player::getShapePPos()
{
    return this->shapePPos;
}

sf::RectangleShape Player::getShape()
{
    return this->shapeP;
}





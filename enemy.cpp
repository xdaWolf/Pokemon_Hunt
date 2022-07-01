#include "enemy.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <experimental/random>
//Constructor / Destructor

Enemy::Enemy()
{
    std::cout << "Enemy Konstruktor" << std::endl;
    std::cout << "Rand:" + std::to_string(std::experimental::randint(1,6)) << std::endl;
    this->textureE.loadFromFile("resources/enemy_" + std::to_string(std::experimental::randint(1,6)) + ".png");
    this->textureE.setSmooth(true);
    this->shapeE.setTexture(&textureE);
    this->shapeE.setSize(sf::Vector2f(this->textureE.getSize().x, this->textureE.getSize().y));
    this->spriteE.setTexture(textureE);
    this->shapeE.setPosition(std::experimental::randint(0,1000),std::experimental::randint(0,600));
    this->spriteE.setPosition(std::experimental::randint(0,1000),std::experimental::randint(0,600));


};

Enemy::~Enemy()
{

    //delete this->field;
};


sf::Sprite Enemy::getSprite()
{
    return this->spriteE;
}





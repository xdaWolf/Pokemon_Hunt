#include "enemy.h"

//Constructor / Destructor

Enemy::Enemy()
{
    this->texturee.loadFromFile("resources/enemy_" + std::to_string(rand() % 6 + 1) + ".png");
    this->shape.setTexture(&texturee);
    this->shape.setSize(sf::Vector2f(this->texturee.getSize().x, this->texturee.getSize().y));
    this->spritee.setTexture(texturee);
    //this->shape.setPosition();
};

Enemy::~Enemy()
{
    //delete this->field;
};

/*
sf::Sprite getSprite()
{
    return this->sprite;
}

*/



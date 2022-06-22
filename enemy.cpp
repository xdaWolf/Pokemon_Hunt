#include "enemy.h"

//Constructor / Destructor

Enemy::Enemy()
{
    this->texture.loadFromFile("resources/enemy_" + std::to_string(rand() % 6 + 1) + ".png");
    this->shape.setTexture(&texture);
    this->shape.setSize(sf::Vector2f(this->texture.getSize().x, this->texture.getSize().y));
    this->sprite.setTexture(texture);
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



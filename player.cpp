#include "Player.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h> //include all necessary external files

Player::Player() : BaseEntity() // constructor
{
    std::cout << "Player constructor" << std::endl;
    setTexture("resources/pikachu_5.png");                                                          // load image of player
    shapeP.setSize(sf::Vector2f(this->getTexture()->getSize().x, this->getTexture()->getSize().y)); // set size of "shape" to player image size
    shapeP.setTexture(this->getTexture());                                                          // set texture of "shape"  to player image
    shapeP.setPosition(sf::Vector2f(spawnPX, spawnPY));                                             // set "shape"  at spawn point
    shapeP.setOrigin(shapeP.getGlobalBounds().width / 2., shapeP.getGlobalBounds().height / 2.);    // move origin of shape  (default: top left) to center of shape
    initializeSpriteAndTexture();
}

Player::~Player() {} // destructor

void Player::initializeSpriteAndTexture()
{
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    sprite.setPosition(sf::Vector2f(spawnPX, spawnPY));                                          // set "sprite" at spawn point
    sprite.setOrigin(sprite.getGlobalBounds().width / 2., sprite.getGlobalBounds().height / 2.); // move origin of sprite (default: top left) to center of sprite
}

void Player::setTexture(const std::string &pTexture) // change texture of player
{
    BaseEntity::setTexture(pTexture);
    sprite.setTexture(*this->getTexture());
    shapeP.setSize(sf::Vector2f(this->getTexture()->getSize().x, this->getTexture()->getSize().y));
    shapeP.setTexture(this->getTexture());
}

int Player::getHealthPoints() { return hp; }        // get health points
void Player::setHealthPoints(int pHp) { hp = pHp; } // set health points

int Player::getCollected() { return collected; }      // get amount of collected Pokemon
void Player::setCollected(int pC) { collected = pC; } // set amount of collected Pokemon

int Player::getSpeed() { return speed; } // get player speed
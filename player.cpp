#include "player.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>

Player::Player()
{
    //SET VARIABLES - PLAYER
    this->speed = 19;
    this->hp = 3;

    //VISUALS - PLAYER
    this->shapePPos = sf::Vector2f(1920 / 2 - 114 / 2, 1080 / 2 - 114 / 2);
    std::cout << "Player Konstruktor" << std::endl;
    this->textureP.loadFromFile("resources/pikachu_5.png");
    this->textureP.setSmooth(true);
    this->shapeP.setTexture(&textureP);
    this->shapeP.setSize(sf::Vector2f(this->textureP.getSize().x, this->textureP.getSize().y));
    this->spriteP.setTexture(textureP);
    this->shapeP.setPosition(shapePPos);
    this->spriteP.setPosition(shapePPos);
    this->spriteP.setOrigin(spriteP.getGlobalBounds().width / 2., spriteP.getGlobalBounds().height / 2.);
    this->shapeP.setOrigin(shapeP.getGlobalBounds().width / 2., shapeP.getGlobalBounds().height / 2.);
    //this->shapeP.setFillColor(sf::Color::Red);
    

};

Player::~Player()
{
    //delete this->field;
};

void Player::setTexture(const std::string& pTexture)
{
    this->textureP.loadFromFile(pTexture);
    this->spriteP.setTexture(textureP);
    this->shapeP.setSize(sf::Vector2f(this->textureP.getSize().x, this->textureP.getSize().y));
    this->shapeP.setTexture(&textureP);
}

int Player::getHealthPoints()
{
    return this->hp;
}

void Player::setHealthPoints(int pHp)
{
    this->hp = pHp;
}

int Player::getSpeed()
{
    return this->speed;
}





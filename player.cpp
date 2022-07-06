#include "player.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>

Player::Player()
{
    //SET VARIABLES - PLAYER
    speed = 13;
    hp = 3;
    collected = 0;

    //VISUALS - PLAYER
    shapePPos = sf::Vector2f(1920 / 2 - 114 / 2, 1080 / 2 - 114 / 2);
    std::cout << "Player Konstruktor" << std::endl;
    textureP.loadFromFile("resources/pikachu_5.png");
    textureP.setSmooth(true);
    shapeP.setTexture(&textureP);
    shapeP.setSize(sf::Vector2f(textureP.getSize().x, textureP.getSize().y));
    spriteP.setTexture(textureP);
    shapeP.setPosition(shapePPos);
    spriteP.setPosition(shapePPos);
    spriteP.setOrigin(spriteP.getGlobalBounds().width / 2., spriteP.getGlobalBounds().height / 2.);
    shapeP.setOrigin(shapeP.getGlobalBounds().width / 2., shapeP.getGlobalBounds().height / 2.);
    //shapeP.setFillColor(sf::Color::Red);
    

};

Player::~Player()
{
    //delete field;
};

void Player::setTexture(const std::string& pTexture)
{
    textureP.loadFromFile(pTexture);
    spriteP.setTexture(textureP);
    shapeP.setSize(sf::Vector2f(textureP.getSize().x, textureP.getSize().y));
    shapeP.setTexture(&textureP);
}

int Player::getHealthPoints()
{
    return hp;
}

void Player::setHealthPoints(int pHp)
{
    hp = pHp;
}

int Player::getSpeed()
{
    return speed;
}





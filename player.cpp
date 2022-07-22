#include "player.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>

Player::Player()
{
    //SET VARIABLES - PLAYER
    speed = 3;
    hp = 3;
    collected = 0;
    canCollect = 1;
    invulnerable = 0;
    spawnPX = 550;
    spawnPY = 200;

    //VISUALS - PLAYER
    shapePPos = sf::Vector2f(spawnPX,spawnPY);
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

int Player::getCollected()
{
    return collected;
}

int Player::getCanCollect()
{
    return canCollect;
}

void Player::setHealthPoints(int pHp)
{
    hp = pHp;
}

void Player::setCanCollect(int pCC)
{
    canCollect = pCC;
}

void Player::setCollected(int pC)
{
    collected = pC;
}

int Player::getSpeed()
{
    return speed;
}

/*int Player::getSpawnzone()
{
    spawnzoneWidth = 360;
    spawnzoneHeight = 150;
    auto spawnzoneBorders = [spawnPX + (textureP.getSize().x / 2) - (spawnzoneWidth / 2); spawnPX + (textureP.getSize().x / 2) + (spawnzoneWidth / 2); spawnPY + (textureP.getSize().y / 2) - (spawnzoneHeight / 2); spawnPY + (textureP.getSize().y / 2) + (spawnzoneHeight / 2)];
    return spawnzoneBorders;
}*/

/*int Player::spawnzoneY(int spawnPY){
    int spawnzoneHeight = 150;
    return spawnPY + (textureP.getSize().y / 2) - (spawnzoneHeight / 2);
}*/


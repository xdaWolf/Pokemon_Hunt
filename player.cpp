#include "player.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>     //include all necessary external files

<<<<<<< Updated upstream
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
    

};

Player::~Player()
{
    //delete this->field;
};
=======

Player::Player()        //constructor
{
    std::cout << "Player constructor" << std::endl;
    textureP.loadFromFile("resources/pikachu_5.png");       //load image of player
    textureP.setSmooth(true);
    shapeP.setSize(sf::Vector2f(textureP.getSize().x, textureP.getSize().y));   //set size of "shape" to player image size
    shapeP.setTexture(&textureP);                           //set texture of "shape"  to player image
    spriteP.setTexture(textureP);                           //set texture of "sprite" to player image
    shapeP.setPosition(sf::Vector2f(spawnPX,spawnPY));                          //set "shape"  at spawn point
    spriteP.setPosition(sf::Vector2f(spawnPX,spawnPY));                         //set "sprite" at spawn point
    spriteP.setOrigin(spriteP.getGlobalBounds().width / 2., spriteP.getGlobalBounds().height / 2.);     //move origin of sprite (default: top left) to center of sprite 
    shapeP.setOrigin(shapeP.getGlobalBounds().width / 2., shapeP.getGlobalBounds().height / 2.);        //move origin of shape  (default: top left) to center of shape
};

Player::~Player(){};    //destructor
>>>>>>> Stashed changes

void Player::setTexture(const std::string& pTexture)        //change texture of player
{
    this->textureP.loadFromFile(pTexture);
    this->spriteP.setTexture(textureP);
}

<<<<<<< Updated upstream
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


=======
int Player::getHealthPoints() { return hp; }                //get health points
void Player::setHealthPoints(int pHp) { hp = pHp; }         //set health points
>>>>>>> Stashed changes

int Player::getCollected() { return collected; }            //get amount of collected Pokemon
void Player::setCollected(int pC) { collected = pC; }       //set amount of collected Pokemon

int Player::getSpeed() { return speed; }                    //get player speed
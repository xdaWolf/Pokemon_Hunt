#include "player.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>                 //include all necessary external files



Player::Player()                    //constructor
{
    //SET VARIABLES - PLAYER
    speed = 9;                      //speed of player, HAS TO BE ODD NUMBER IN ORDER FOR ANIMATIONS TO WORK PROPERLY
    hp = 3;                         //health points of player
    collected = 0;                  //amount of collected Pokemon
    spawnPX = 550;                  //horizontal spawn point of player
    spawnPY = 200;                  //vertical spawn point of player

    //VISUALS - PLAYER
    shapePPos = sf::Vector2f(spawnPX,spawnPY);          //spawn point of player
    std::cout << "Player Konstruktor" << std::endl;
    textureP.loadFromFile("resources/pikachu_5.png");   //load image of player
    textureP.setSmooth(true);
    shapeP.setSize(sf::Vector2f(textureP.getSize().x, textureP.getSize().y));   //set size of "shape" to player image
    shapeP.setTexture(&textureP);                       //set texture of "shape"  to player image
    spriteP.setTexture(textureP);                       //set texture of "sprite" to player image
    shapeP.setPosition(shapePPos);                      //set "shape"  at spawn point
    spriteP.setPosition(shapePPos);                     //set "sprite" at spawn point
    spriteP.setOrigin(spriteP.getGlobalBounds().width / 2., spriteP.getGlobalBounds().height / 2.);     //move origin of sprite (default: top left) to center of sprite 
    shapeP.setOrigin(shapeP.getGlobalBounds().width / 2., shapeP.getGlobalBounds().height / 2.);        //move origin of shape  (default: top left) to center of shape
    

};

Player::~Player()       //destructor
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

int Player::getHealthPoints() { return hp; }                //get health points
void Player::setHealthPoints(int pHp) { hp = pHp; }         //set health points

int Player::getCollected() { return collected; }            //get amount of collected Pokemon
void Player::setCollected(int pC) { collected = pC; }       //set amount of collected Pokemon


int Player::getSpeed()
{
    return speed;                       //get player speed
}

/*int Player::getSpawnzone()
{
    spawnzoneWidth = 360;
    spawnzoneHeight = 150;
    int spawnzoneBorders = [spawnPX + (textureP.getSize().x / 2) - (spawnzoneWidth / 2); spawnPX + (textureP.getSize().x / 2) + (spawnzoneWidth / 2); spawnPY + (textureP.getSize().y / 2) - (spawnzoneHeight / 2); spawnPY + (textureP.getSize().y / 2) + (spawnzoneHeight / 2)];
    return spawnzoneBorders;
}*/

/*int Player::spawnzoneY(int spawnPY){
    int spawnzoneHeight = 150;
    return spawnPY + (textureP.getSize().y / 2) - (spawnzoneHeight / 2);
}*/


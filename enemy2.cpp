#include "enemy2.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h>

//Constructor / Destructor

Enemy2::Enemy2()
{
    std::cout << "Enemy2 Konstruktor" << std::endl;
    speed = fRand(1.5,3.5);
    std::cout << "Enemy2 Speed:" + std::to_string(speed) << std::endl;
    textureE2.loadFromFile("resources/pokeball_" + std::to_string(giveRandomNumber(1,5)) + ".png");
    textureE2.setSmooth(true);
    shapeE2.setTexture(&textureE2);
    shapeE2.setSize(sf::Vector2f(textureE2.getSize().x, textureE2.getSize().y));
    spriteE2.setTexture(textureE2);
    int positionX,positionY;
    positionX = 1920 - textureE2.getSize().x;
    positionY = giveRandomNumber(0,1080);
    shapeE2.setPosition(positionX,positionY); 
    spriteE2.setPosition(positionX,positionY); 
};

Enemy2::~Enemy2()
{

    //delete field;
};


sf::Sprite Enemy2::getSprite()
{
    return spriteE2;
}

int Enemy2::giveRandomNumber(int pMin, int pMax)
{
    auto start = std::chrono::steady_clock::now();
    int dfe = 100;                                  //distance from edges (in pixels, maybe implement automatic number here using size of respective sprite)
    Sleep(10);
    auto end = std::chrono::steady_clock::now();
    int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();    //get a pseudo-random number by counting the microseconds it took the program to process the lines above

    if(pMax < 100)                                  //allows up to 99 different sprites for enemies, requirement: window size is 100x100px or larger
    {
        return microseconds % pMax + pMin;          //select random sprite

    } else
    {
        int spawnheight = microseconds % (pMax - 2*dfe) + dfe;      //select random position for enemy to spawn (considering the set distance from edges)
        if(spawnheight >= 200 && spawnheight < 320) //in case the pokeball tries to spawn within the player's vertical spawn position
        {
            return 320;                             //have it spawn right below the player instead (number to return = player y spawn + player y size)

        } else {
            return spawnheight;                     //otherwise keep the random spawn height
        } 
    }
}

double Enemy2::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
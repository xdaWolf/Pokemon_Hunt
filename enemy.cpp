#include "enemy.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h>        //include all necessary external files

Enemy::Enemy()              //constructor
{
    std::cout << "Enemy constructor" << std::endl;
    textureE.loadFromFile("resources/enemy_" + std::to_string(giveRandomNumber(1,6)) + ".png");     //select random trainer image
    textureE.setSmooth(true); 
    spriteE.setTexture(textureE);                   //set texture of "sprite" to trainer image
    int positionX,positionY;
    positionX = giveRandomNumber(0,1920);           //select random horizontal spawn point
    positionY = giveRandomNumber(0,900);            //select random vertical spawn point
    spriteE.setPosition(positionX,positionY);       //set sprite at spawn point
};

Enemy::~Enemy(){};          //destructor

int Enemy::giveRandomNumber(int pMin, int pMax)
{
    auto start = std::chrono::steady_clock::now();
    int dfe = 100;                                      //distance from edges (in pixels, implementation idea: automatic number using size of respective sprite)
    Sleep(10);
    auto end = std::chrono::steady_clock::now();
    int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();    //get a pseudo-random number by counting the microseconds it took the program to process the lines above

    if(pMax < 100)                                      //allows up to 99 different sprites for enemies, requirement: window size is 100x100px or larger
    {
        return microseconds % pMax + pMin;              //select random sprite
    } else
    {
        return microseconds % (pMax - 2*dfe) + dfe;     //select random position for enemy to spawn (considering the set distance from edges)
    }
}

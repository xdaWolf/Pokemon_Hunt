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
    speed = giveRandomSpeed(0.5,2.0);
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
    int dfe = 150;  //distance from edges (in pixels, maybe implement automatic number here using size of respective sprite)
    int phss = 20;  //possible horizontal spawn spots (should be below lowest elapsed time and below average difference in elapsed times)          //hier müsste man noch ein zweiten phss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    int pvss = 5;   //possible vertical spawn spots   (                                       ~                                         )          //hier müsste man noch ein zweiten pvss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    Sleep(10);
    auto end = std::chrono::steady_clock::now();
    int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    if(pMax == 5)
    {
        //return microseconds % 6 + 1;
        return microseconds % 5 + pMin;
    } else if (pMax == 1080)
    {
        //return microseconds % pvss * (int((1080 - 2*dfe) / (pvss-1))) + dfe; 
        return microseconds % (1080 - 2*dfe) + dfe;
    } else if(pMax == 1920)
    {
        //return microseconds % pvss * (int((1920 - 2*dfe) / (pvss-1))) + dfe;
        return microseconds % (1920 - 2*dfe) + dfe;
    }

    //prefer fewer equally distributed spots across       //maybe implement automatic window size detection here

    //the map than many spots all close to each other
    //if(abs(enemy1.shapeE.x - enemy2.shapeE.x) < shapeE.width) enemy2.shapeE.x += shapeE.width or -= if close to right edge idk or y coordinates or spriteE x/y idk xd (solution in case enemy spawns overlap (only 100 spawn spots available))
}

double Enemy2::giveRandomSpeed(double pMin, double pMax)
{
    auto start = std::chrono::steady_clock::now();
    int dfe = 150;  //distance from edges (in pixels, maybe implement automatic number here using size of respective sprite)
    int phss = 20;  //possible horizontal spawn spots (should be below lowest elapsed time and below average difference in elapsed times)          //hier müsste man noch ein zweiten phss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    int pvss = 5;   //possible vertical spawn spots   (                                       ~                                         )          //hier müsste man noch ein zweiten pvss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    Sleep(10);
    auto end = std::chrono::steady_clock::now();
    double microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    if(pMax == 2.0)
    {
        return (dmod(microseconds,2.0)) + pMin;
    }
}

double Enemy2::dmod(double x, double y) 
{
    return x - (int)(x/y) * y;
}
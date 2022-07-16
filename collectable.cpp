#include "collectable.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h>

Collectable::Collectable()
{
    std::cout << "Collectable Konstruktor" << std::endl;
    //SET VARIABLES - COLLECTABLE
    collected = 0;
    textureC.loadFromFile("resources/collectable_" + std::to_string(giveRandomNumber(1,6)) + ".png");
    textureC.setSmooth(true);
    shapeC.setTexture(&textureC);
    shapeC.setSize(sf::Vector2f(textureC.getSize().x, textureC.getSize().y));
    spriteC.setTexture(textureC);
    int positionX,positionY;
    positionX = giveRandomNumber(0,1920);
    positionY = giveRandomNumber(0,1080);
    shapeC .setPosition(positionX,positionY);    
    spriteC.setPosition(positionX,positionY);
};

Collectable::~Collectable()
{

};

int Collectable::giveRandomNumber(int pMin, int pMax)
{
    auto start = std::chrono::steady_clock::now();
    int dfe = 100;  //distance from edges (in pixels, maybe implement automatic number here using size of respective sprite)
    int phss = 20;  //possible horizontal spawn spots (should be below lowest elapsed time and below average difference in elapsed times)          //hier müsste man noch ein zweiten phss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    int pvss = 5;   //possible vertical spawn spots   (                                       ~                                         )          //hier müsste man noch ein zweiten pvss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    Sleep(10);
    auto end = std::chrono::steady_clock::now();

    int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    if(pMax == 6)
    {
        //return microseconds % 6 + 1;
        return microseconds % 6 + 1;
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

sf::Sprite Collectable::getSprite()
{
    return spriteC;

}
#include "collectable.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
<<<<<<< Updated upstream
=======
#include <windows.h>            //include all necessary external files
>>>>>>> Stashed changes



Collectable::Collectable()      //constructor
{
<<<<<<< Updated upstream
    std::cout << "Collectable Konstruktor" << std::endl;
    auto start = std::chrono::steady_clock::now();
    std::cout << "Enemy Konstruktor" << std::endl;
    int dfe = 150;  //distance from edges (in pixels, maybe implement automatic number here using size of respective sprite)
    int phss = 20;  //possible horizontal spawn spots (should be below lowest elapsed time and below average difference in elapsed times)          //hier müsste man noch ein zweiten phss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    int pvss = 5;   //possible vertical spawn spots   (                                       ~                                         )          //hier müsste man noch ein zweiten pvss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    auto end = std::chrono::steady_clock::now();
    int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout << "Microseconds: " << microseconds << std::endl;
    //SET VARIABLES - COLLECTABLE
    this->textureC.loadFromFile("resources/collectable_" + std::to_string(microseconds % 6 + 1) + ".png");
    this->textureC.setSmooth(true);
    this->shapeC.setTexture(&textureC);
    this->shapeC.setSize(sf::Vector2f(this->textureC.getSize().x, this->textureC.getSize().y));
    this->spriteC.setTexture(textureC);
    this->shapeC .setPosition(microseconds % phss * (int((1920 - 2*dfe) / (phss-1))) + dfe, microseconds % pvss * (int((1080 - 2*dfe) / (pvss-1))) + dfe);    //prefer fewer equally distributed spots across       //maybe implement automatic window size detection here
    this->spriteC.setPosition(microseconds % phss * (int((1920 - 2*dfe) / (phss-1))) + dfe, microseconds % pvss * (int((1080 - 2*dfe) / (pvss-1))) + dfe);    //the map than many spots all close to each other
};

Collectable::~Collectable()
{

};

sf::Sprite Collectable::getSprite()
{
    return this->spriteC;

=======
    std::cout << "Collectable constructor" << std::endl;
    textureC.loadFromFile("resources/collectable_" + std::to_string(giveRandomNumber(1,6)) + ".png");   //select random Pokemon image
    textureC.setSmooth(true);
    spriteC.setTexture(textureC);                       //set texture of "sprite" to Pokemon image
    int positionX,positionY;
    positionX = giveRandomNumber(0,1920);               //select random horizontal spawn point
    positionY = giveRandomNumber(0,900);                //select random vertical spawn point
    spriteC.setPosition(positionX,positionY);           //set "sprite" at spawn point
};

Collectable::~Collectable(){};  //destructor

int Collectable::giveRandomNumber(int pMin, int pMax)
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
>>>>>>> Stashed changes
}
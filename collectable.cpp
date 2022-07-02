#include "collectable.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>

Collectable::Collectable()
{
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

}
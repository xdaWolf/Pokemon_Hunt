#include "enemy.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
<<<<<<< Updated upstream
=======
#include <windows.h>        //include all necessary external files
>>>>>>> Stashed changes


Enemy::Enemy()              //constructor
{
<<<<<<< Updated upstream
    auto start = std::chrono::steady_clock::now();
    std::cout << "Enemy Konstruktor" << std::endl;
    int dfe = 150;  //distance from edges (in pixels, maybe implement automatic number here using size of respective sprite)
    int phss = 20;  //possible horizontal spawn spots (should be below lowest elapsed time and below average difference in elapsed times)          //hier müsste man noch ein zweiten phss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    int pvss = 5;   //possible vertical spawn spots   (                                       ~                                         )          //hier müsste man noch ein zweiten pvss erstellen, wenn shapeE und spriteE verschiedene Positionen haben sollen
    auto end = std::chrono::steady_clock::now();
    int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout << "Microseconds: " << microseconds << std::endl;
    this->textureE.loadFromFile("resources/enemy_" + std::to_string(microseconds % 6 + 1) + ".png");
    this->textureE.setSmooth(true);
    this->shapeE.setTexture(&textureE);
    this->shapeE.setSize(sf::Vector2f(this->textureE.getSize().x, this->textureE.getSize().y));
    this->spriteE.setTexture(textureE);
    this->shapeE .setPosition(microseconds % phss * (int((1920 - 2*dfe) / (phss-1))) + dfe, microseconds % pvss * (int((1080 - 2*dfe) / (pvss-1))) + dfe);    //prefer fewer equally distributed spots across       //maybe implement automatic window size detection here
    this->spriteE.setPosition(microseconds % phss * (int((1920 - 2*dfe) / (phss-1))) + dfe, microseconds % pvss * (int((1080 - 2*dfe) / (pvss-1))) + dfe);    //the map than many spots all close to each other
    //if(abs(enemy1.shapeE.x - enemy2.shapeE.x) < shapeE.width) enemy2.shapeE.x += shapeE.width or -= if close to right edge idk or y coordinates or spriteE x/y idk xd (solution in case enemy spawns overlap (only 100 spawn spots available))
};

Enemy::~Enemy()
{

    //delete this->field;
};


sf::Sprite Enemy::getSprite()
{
    return this->spriteE;
}




//Grundsätzliche Idee für Pokeballmovement:
//position -= ~10
//if position.x < -100, position.x += 2120, position.y = (position.y + playerpos.x) % 1080 (random spot on y-axis based on player's x position)
//Phase 2: when collectable eingesammelt, neues Pokeballobjekt erzeugen, evtl. nich random machen, sondern Phase 1 ein normaler, Phase 2 zwei Superbälle, dann drei Meisterbälle/vier Ultrabälle oder wie die heißen xD
=======
    std::cout << "Enemy constructor" << std::endl;
    textureE.loadFromFile("resources/enemy_" + std::to_string(giveRandomNumber(1,6)) + ".png");     //select random Trainer image
    textureE.setSmooth(true); 
    spriteE.setTexture(textureE);                   //set texture of "sprite" to Trainer image
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
>>>>>>> Stashed changes

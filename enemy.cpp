#include "enemy.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>

//Constructor / Destructor

Enemy::Enemy()
{
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
    //this->shapeE.setFillColor(sf::Color::Red);
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
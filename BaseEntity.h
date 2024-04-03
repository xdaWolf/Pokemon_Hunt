#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp> //include all necessary external files

#ifndef BASEENTITY_H_
#define BASEENTITY_H_
using namespace sf;
/*
    BaseEntity class: abstract Base Class that defines basic properties of the entities in the game
*/

class BaseEntity
{
private:
    // VARIABLES
    Texture texture; // texture

public:
    BaseEntity();  // constructor
    ~BaseEntity(); // destructor

    // VISUALS
    Sprite sprite; // sprite
    void setTexture(const std::string &pTexturePath);
    const Texture *getTexture() const;
    virtual int giveRandomNumber(int pMin, int pMax);  // randomization of Pokemon spawn location
    double giveRandomDouble(double pMin, double pMax); // randomization of Pokeball speed
    virtual void initializeSpriteAndTexture();         // initialize sprite and texture                          // abstract method
};

#endif
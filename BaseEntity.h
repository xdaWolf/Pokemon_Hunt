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
    Texture texture;

public:
    // VARIABLES
    Sprite sprite;

    // METHODS
    BaseEntity();  // constructor
    ~BaseEntity(); // destructor

    void setTexture(const std::string &pTexturePath);
    const Texture *getTexture() const;
    virtual int giveRandomNumber(int pMin, int pMax);  // returns the random number (int) between pMin and pMax
    double giveRandomDouble(double pMin, double pMax); // returns the random number (double) between pMin and pMax
    virtual void initializeSpriteAndTexture();         // initialize sprite and texture
};

#endif
#pragma once

#include <SFML/Audio.hpp>

#ifndef SOUNDS_H_
#define SOUNDS_H_

using namespace sf;
/*
    Sounds class: holds the sounds that are used in the game
*/

class Sounds
{
private:
public:
    // VARIABLES
    Sound collected, win, failure, damage;
    SoundBuffer bufferC, bufferW, bufferF, bufferD;
    // METHODS
    Sounds();  // constructor
    ~Sounds(); // destructor
};

#endif
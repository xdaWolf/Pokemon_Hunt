#include "Sounds.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h> //include all necessary external files

Sounds::Sounds() // constructor
{
    std::cout << "Sounds constructor" << std::endl;
    bufferC.loadFromFile("resources/collected.wav"); // load sound files
    bufferW.loadFromFile("resources/win.wav");
    bufferF.loadFromFile("resources/failure.wav");
    bufferD.loadFromFile("resources/damage.wav");

    collected.setBuffer(bufferC); // set sound buffers
    win.setBuffer(bufferW);
    failure.setBuffer(bufferF);
    damage.setBuffer(bufferD);

    collected.setVolume(70); // set volume for each sound effect
    win.setVolume(55);
    failure.setVolume(25);
    damage.setVolume(35);
}

Sounds::~Sounds() {} // destructor
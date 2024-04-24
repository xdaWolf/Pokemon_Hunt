#pragma once

#include "BaseEntity.h" //include all necessary external files

#ifndef ENDOFGAME_H_
#define ENDOFGAME_H_
using namespace sf;
/*
    EndOfGame class: used to display pictures at the end of the game
*/

class EndOfGame : public BaseEntity
{
private:
public:
    // METHODS
    EndOfGame();  // constructor
    ~EndOfGame(); // destructor
};

#endif
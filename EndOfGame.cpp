#include "EndOfGame.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

EndOfGame::EndOfGame() : BaseEntity() // constructor
{
    std::cout << "EndOfGame constructor" << std::endl;
}

EndOfGame::~EndOfGame() {} // destructor

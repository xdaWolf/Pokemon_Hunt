#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "game.h"

//in cmd type: mingw32-make

Game game;

int main(int argc, char* argv[])
{

    Field field = game.getField();
    
    
    while (field.getFieldIsOpen())
    {
        // Update
        field.update();


        // Render
        field.render();

    }

    return 0;
}
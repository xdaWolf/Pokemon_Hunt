#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "game.h"

//in cmd type: mingw32-make

Game game;

int main(int argc, char* argv[])
{
    std::cout << "Start" << std::endl;

    Field field = game.getField();
    
    //std::cout << "getField():" +  game.getField().getFieldIsOpen() << std::endl;
    
    while (field.getFieldIsOpen())
    {
        std::cout << "in While" << std::endl;
        // Update
        field.update();
        std::cout << "Update" << std::endl;

        // Render
        field.render();
        std::cout << "Render" << std::endl;

    }

    return 0;
}
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>


#include "game.h"

//in cmd type: mingw32-make

int main(int argc, char* argv[])
{

    //using namespace sf;

    // init Game engine
    class Game game;
    game = Game();

    // Game loop

    while (game.getField().getFieldIsOpen())
    {
        // Update
        game.getField().update();

        // Render
        game.getField().render();

    }

    return 0;
}
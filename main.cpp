#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "game.h"

//In Konsole: mingw32-make und dann main

int main(int argc, char* argv[])
{
    using namespace sf;

    // init Game engine
    Game game;

    // Game loop

    while (game.getWindowIsOpen())
    {
        // Update
        game.update();

        // Render
        game.render();

    }

    return 0;
}
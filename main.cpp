/*
Pokemon-Hunt
Authors:        Sarah Holzmann, Niklas Meier
Created:        20.05.2022
Last updated:   24.04.2024
Version:        1.0

How to play:
- to start the game, open your cmd and type "make" (make sure your in the path of this project, windows: cd("path/to/Pokemon_Hunt")).
- execute ./main.exe
- use make clean to delete .o files

- move your character (Pikachu) through keys WASD.
- open the menu by pressing M, allows changing gamemode
- Gamemode Normal:
- collect all other Pokemon on the field while avoiding Pokeballs and Trainers. After you've collected all three Pokemon, head towards the Pokecenter to win.
- the less moves you make and the more HP you have left, the better your score.
- getting hit three times results in Game Over.
- pressing R at any point restarts the game. To get a new Pokemon/Trainer/Tree layout, restart the program.
- to end the game, press Escape or close the window.
- Gamemode Survival:
- try not to get hit by pokeballs
- once you got hit 3 times the survived time is displayed

How to test:
- to test the game, open your cmd and type "make test" (make sure your in the path of this project, windows: cd("path/to/Pokemon_Hunt")).
- execute ./test.exe

When editing the code, make sure to look out for comments starting with "IMPORTANT"!
When adding new sprites, format the file names like this: "<nameOfSprite>_<nextNumber>"


Note:
- "Collectable" and "Pokemon" are used synonymously.
- "CPB" is short for "collected Pokemon box"
*/

#include "SurvivalGameMode.h"
#include "NormalGameMode.h"
#include "Field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h> //include all necessary external files

int main(int argc, char *argv[])
{
    Field field;
    NormalGameMode *normalGameMode = new NormalGameMode(&field);
    SurvivalGameMode *survivalGameMode = new SurvivalGameMode(&field);

    sf::Music backgroundmusic;                                     // variable used for background music
    backgroundmusic.openFromFile("resources/backgroundmusic.wav"); // if you dont have the correct file, you should comment these lines out
    backgroundmusic.setVolume(100);
    backgroundmusic.play(); // start the background music

    field.attach(&field.player); // attach player to fields observer list

    while (field.getFieldIsOpen()) // as long as field wasn't closed
    {
        if (field.gamemode == 0)
        {
            normalGameMode->update();
            normalGameMode->render();
        }
        else
        {
            survivalGameMode->update();
            survivalGameMode->render();
        }
    }

    return 0; // return 0 if game was closed successfully
}

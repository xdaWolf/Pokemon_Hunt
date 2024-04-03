/*
Pokemon-Hunt
Authors:        Sarah Holzmann, Niklas Meier
Created:        20.05.2022
Last updated:   28.07.2022
Version:        1.0

How to play:
- to start the game, open your cmd and type "mingw32-make" (make sure your in the path of this project).
- move your character (Pikachu) through keys WASD.
- collect all other Pokemon on the field while avoiding Pokeballs and Trainers. After you've collected all three Pokemon, head towards the Pokecenter to win.
- the less moves you make and the more HP you have left, the better your score.
- getting hit three times results in Game Over.
- pressing R at any point restarts the game. To get a new Pokemon/Trainer/Tree layout, restart the program.
- to end the game, press Escape or close the window.

When editing the code, make sure to look out for comments starting with "IMPORTANT"!
When adding new sprites, format the file names like this: "<nameOfSprite>_<nextNumber>"


Note:
- "Collectable" and "Pokemon" are used synonymously.
- "CPB" is short for "collected Pokemon box"
*/

#include "Field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h> //include all necessary external files

int main(int argc, char *argv[])
{
    Field field; // create a field to play on

    sf::Music backgroundmusic;                                     // variable used for background music
    backgroundmusic.openFromFile("resources/backgroundmusic.wav"); // load background music file
    backgroundmusic.setVolume(30);                                 // set volume of background music
    backgroundmusic.play();                                        // start the background music

    while (field.getFieldIsOpen()) // as long as field wasn't closed
    {
        field.update(); // update the current field

        field.render(); // render the updated field
    }

    return 0; // return 0 if game was closed successfully
}

/*
Pokemon-Hunt
Authors:        Sarah Holzmann, Niklas Meier
Created:        20.05.2022
Last updated:   22.07.2022
Version:        0.25.2

How to play:
- to start the game, open your cmd and type "mingw32-make".
- move your character (Pikachu) through keys WASD.
- collect all other Pokemon on the field while avoiding Pokeballs and Trainers. After you've collected all three Pokemon, head towards the Pokecenter to win.
- getting hit three times results in Game Over. Pressing R restarts the game.
- to end the game, press Escape.
*/



#include "game.h" 

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>                     //include all necessary external files



Game game;                              //create a game

int main(int argc, char* argv[])
{
    Field field = game.getField();      //create a field to play on
    
    while (field.getFieldIsOpen())      //as long as field wasn't closed
    {
        field.update();                 //update the current field

        field.render();                 //render the updated field
    }

    return 0;                           //return 0 if program was closed successfully
}
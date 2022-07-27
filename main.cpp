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
- the less moves you make and the more HP you have left, the better your score.
- getting hit three times results in Game Over.
- pressing R at any point restarts the game. To get a new Pokemon/Trainer/Tree layout, restart the program.
- to end the game, press Escape.
- When editing the code, make sure to look out for comments starting with "IMPORTANT"!
- "Collectable" and "Pokemon" are used synonymously.
- "Enemy(1)" and "Trainer" are used synonymously.
- "Enemy(2)" and "Pokeballs" are used synonymously.
*/



//#include "game.h" 
#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>                     //include all necessary external files
#include <windows.h>

int main(int argc, char* argv[])
{
    
    Field field;                        //create a field to play on
    
    sf::Music backgroundmusic;
    backgroundmusic.openFromFile("resources/backgroundmusic.wav");
    backgroundmusic.setVolume(50);
    backgroundmusic.play();

    while (field.getFieldIsOpen())      //as long as field wasn't closed
    {
        field.update();                 //update the current field

        field.render();                 //render the updated field
    }

    return 0;                           //return 0 if program was closed successfully
}
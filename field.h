#pragma once

#include "enemy.h"
#include "player.h"
#include "collectable.h"
#include "enemy2.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>    //include all necessary external files


#ifndef FIELD_H_
#define FIELD_H_

/*
    Class that is used to create, update and display the gamefield
*/

class Field
{
    private:
    //PRIVATE VARIABLES
    int moves;                      //counts amount of moves player did before finishing
    int score;                      //used to calculate score, moves is used
    int direction;                  //saves in which direction the player is moving
    int playerPosX, playerPosY;     //saves position of player (X & Y)
    int amountOfTrees = 4;          //IMPORTANT: this number + the amount of invisible rectangles (default: 2) has to be equal to spriteTree/textureTree array size as declared below
    int positionCX[3];              //IMPORTANT: same number as collectables array size and positionCY
    int positionCY[3];              //IMPORTANT: same number as collectables array size and positionCX
    int success;                    //acts as bool, saves whether player has won

    sf::Time InputDelay = sf::seconds(0.0001f);         //input delay, added for smooth movement
    sf::Clock InputDelayTimer;                          //timer, added for smooth movement

    //SOUND
    sf::Sound collected, win, failure, damage;
    sf::SoundBuffer bufferC, bufferW, bufferF, bufferD;

    //OBJECTS
    //amount of each object (trainers, Pokeballs, Pokemon, trees), reduce any to lower difficulty (and vice versa)
    Player player;
    Enemy enemies[4];
    Enemy2 pokeballs[5];
    Collectable collectables[3];    //IMPORTANT: same number as positionCX and positionCY
    sf::Sprite spriteTree[6];       //IMPORTANT: this number is the sum of amountOfTrees and amount of transparent rectangles. Check "amountOfTrees" variable. Maybe implement vector here.
    sf::Texture textureTree[6];     //IMPORTANT: this number is the sum of amountOfTrees and amount of transparent rectangles. Check "amountOfTrees" variable. Maybe implement vector here.
    
    //PRIVATE VISUALS
    sf::RenderWindow* field;        //field is realised as renderwindow

    sf::Sprite spritef;             //visuals for field
    sf::Texture texturef;

    sf::Sprite spriteHB;            //visuals for health bar
    sf::Texture textureHB;

    sf::Sprite spriteCPB;           //visuals for collected Pokemon box
    sf::Texture textureCPB;

    sf::Sprite spritePC;            //visuals for PokeCenter
    sf::Texture texturePC;

    sf::Sprite spriteEOGS;          //visuals for endOfGame success/death sprite
    sf::Texture textureEOGS;

    sf::Sprite spriteEOGM;          //visuals for endOfGame success/death message
    sf::Texture textureEOGM;

    sf::Font pokemonhollow;         //visuals for score
    sf::Text textscore;

    //PRIVATE METHODS
    void pokeballMovement();        //moves Pokeballs
    void checkCollision();          //checks for any collision between sprites on the field
    void updateHealth();            //update health of player
    void endOfGame(int success);    //success/death screen
    void resetGame();               //resets the game
    void checkPositions();          //checks whether any objects spawned on top of each other
    

    public:
    Field();            //constructor
    ~Field();           //destructor

    //PUBLIC METHODS
    void update();      //update the game data
    void render();      //draw updated field and display it
    //Get-Methods
    const bool getFieldIsOpen() const;  //get whether the field is still opened

};

#endif

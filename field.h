#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "enemy.h"
#include "player.h"
#include "collectable.h"
#include "enemy2.h"

#ifndef FIELD_H_
#define FIELD_H_

/*
    Class that is used to create the gamefield, display the gamefiled and manage data to rule the game
*/

class Field
{
    
    private:
    //VARIABLES
    int moves;              //counts amount of needed moves for completing level
    int score;              //used to calculate score, moves is used
    int direction;          //saves in which direction the player is moving
    int playerPosX, playerPosY;         //saves position of player (X&Y)
    int amountOfTrees = 4; //IMPORTANT: this number + the amount of invisible rectangles (= amount of else if's below) has to be equal to spriteTree/textureTree array size as declared in field.h
    int positionCX[3];              //IMPORTANT: same number as amount of collectables and positionCX
    int positionCY[3];              //IMPORTANT: same number as amount of collectables and positionCY

    sf::Time InputDelay = sf::seconds(0.0001f);         //Input-Delay, was added for smooth movement
    sf::Clock InputDelayTimer;                          //Timer, was also added for smooth movement

    //SOUND
    sf::Sound collected, failure, win, damage;
    sf::SoundBuffer bufferC,bufferF,bufferW, bufferD;

    //OBJECTS
    //amount of each object (Trainers, Pokeballs, Pokemon, Trees), reduce any to lower difficulty and vice versa
    Player player;
    Enemy enemies[4];
    Enemy2 pokeballs[5];
    Collectable collectables[3];    //IMPORTANT: same number as positionCX and positionCY
    
    //VISUALS
    sf::RenderWindow* field;        //field is realised as renderwindow

    sf::Sprite spriteTree[6];       //IMPORTANT: this number is the sum of amount of trees and amount of transparent rectangles. Check "amountOfTrees" variable. Maybe implement vector here.
    sf::Texture textureTree[6];     //IMPORTANT: this number is the sum of amount of trees and amount of transparent rectangles. Check "amountOfTrees" variable. Maybe implement vector here.

    sf::Sprite spriteCPB;           //Visuals for Collected Pokemon Box
    sf::Texture textureCPB;
    
    sf::Sprite spriteHP;            //Visuals for Health BAr
    sf::Texture textureHP;

    sf::Sprite spritePC;            //Visuals for PokeCenter
    sf::Texture texturePC;

    sf::Sprite spritef;             //Visuals for Field
    sf::Texture texturef;

    sf::Sprite spriteDS;            //Visuals for Death-Screen
    sf::Texture textureDS;

    sf::Sprite spriteDM;            //Visuals for Death-Message
    sf::Texture textureDM;

    sf::Sprite spriteSS;            //Visuals for Winner-Screen
    sf::Texture textureSS;

    sf::Sprite spriteSM;            //Visuals for Success-Message
    sf::Texture textureSM;

    sf::Font pokemonhollow;         //Visuals for Score
    sf::Text textscore;

    //METHODS
    void checkCollision();          //checks for any collision between sprites on the field
    void updateHealth();            //is called to update health of playerPosY
    void resetGame();               //resets the game for new try
    void checkPositions();          //checks at the beginning, if any objects are on top of each other
    void checkForWin();             //checks, if player has won
    void pokeballMovement();        //moves pokeballs
    
    public:

    Field();            //constructor
    ~Field();           //destructor

    //METHODS
    void update();      //update the game data
    void render();      //draw updated field and display it
    
    //Get-Methods
    const bool getFieldIsOpen() const;

};

#endif

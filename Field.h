#pragma once

#include "Player.h"
#include "Collectable.h"
#include "Trainer.h"
#include "Pokeball.h"
#include "EndOfGame.h"
#include "HealthBar.h"
#include "PokeBox.h"
#include "PokeCenter.h"
#include "Obstacle.h"
#include "Menu.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp> //include all necessary external files

#ifndef FIELD_H_
#define FIELD_H_

/*
    Class that is used to create, update and display the gamefield
*/

class Field
{
private:
    // PRIVATE VARIABLES
    int moves;                  // counts amount of moves player did before finishing
    int score;                  // used to calculate score, moves is used
    int direction;              // saves in which direction the player is moving
    int playerPosX, playerPosY; // saves position of player (X & Y)
    int positionCX[3];          // IMPORTANT: same number as collectables array size and positionCY
    int positionCY[3];          // IMPORTANT: same number as collectables array size and positionCX
    int success;                // acts as bool, saves whether player has won
    bool menuIsOpen;            // saves whether menu is open
    bool prevMenuKeyPressed;    // saves whether menu key was pressed in previous frame

    sf::Time InputDelay = sf::seconds(0.0001f); // input delay, added for smooth movement
    sf::Clock InputDelayTimer;                  // timer, added for smooth movement

    // SOUND
    sf::Sound collected, win, failure, damage;
    sf::SoundBuffer bufferC, bufferW, bufferF, bufferD;

    // OBJECTS
    // amount of each object (trainers, Pokeballs, Pokemon, trees), reduce any to lower difficulty (and vice versa)
    Player player;
    Trainer trainers[4];
    Pokeball pokeballs[5];

    Collectable collectables[3]; // IMPORTANT: same number as positionCX and positionCY
    // sf::Sprite spriteTree[6];    // IMPORTANT: this number is the sum of amountOfTrees and amount of transparent rectangles. Check "amountOfTrees" variable. Maybe implement vector here.
    // sf::Texture textureTree[6];  // IMPORTANT: this number is the sum of amountOfTrees and amount of transparent rectangles. Check "amountOfTrees" variable. Maybe implement vector here.

    Obstacle trees[3];

    Obstacle mountainTopRight;
    Obstacle mountainTopLeft;

    // PRIVATE VISUALS
    sf::RenderWindow *field; // field is realised as renderwindow

    sf::Sprite spritef; // visuals for field
    sf::Texture texturef;

    HealthBar healthbar;

    PokeBox pokebox;

    PokeCenter pokecenter;

    EndOfGame endOfGameSprite;  // visuals for endOfGame success/death sprite
    EndOfGame endOfGameMessage; // visuals for endOfGame success/death message

    sf::Font pokemonhollow; // visuals for score
    sf::Text textscore;

    Menu menu;
    sf::RectangleShape dimOverlay; // set colour of rectangle to transparent

    // PRIVATE METHODS
    void pokeballMovement();      // moves Pokeballs
    void checkCollision();        // checks for any collision between sprites on the field
    void updateHealth();          // update health of player
    void endOfGame(int pSuccess); // success/death screen
    void resetGame();             // resets the game
    void checkPositions();        // checks whether any objects spawned on top of each other
    void openMenu();              // opens the menu
    void closeMenu();             // closes the menu

    /*
    template <typename T>
    void checkOverlap(sf::Sprite &entity, T &entities);
    template <typename T, typename U>
    void checkOverlap(T &group1, U &group2);
    void setNewPosition(sf::Sprite &entity);
    */
public:
    Field();  // constructor
    ~Field(); // destructor

    // PUBLIC METHODS
    void update(); // update the game data
    void render(); // draw updated field and display it
    // Get-Methods
    const bool getFieldIsOpen() const; // get whether the field is still opened
    const bool getMenuIsOpen() const;  // get whether the menu is open
};

#endif
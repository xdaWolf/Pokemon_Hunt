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
#include "Sounds.h"
#include "Subject.h"
#include "Observer.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <vector> //include all necessary external files
#include <chrono>

#ifndef FIELD_H_
#define FIELD_H_

/*
    Field Class: Class that is used to create, update and display the gamefield, including all objects and the player.
*/

class Field : public Subject
{
private:
    // VARIABLES
    int score;   // used to calculate score, moves is used
    int success; // acts as bool, saves whether player has won
    // OBJECTS
    sf::Clock healthUpdateTimer; // Timer for spawn proof in survival mode
    sf::Time SpawnProof = sf::seconds(3);

    Sounds sounds;

    sf::Texture texturef;
    EndOfGame endOfGameSprite;  // visuals for endOfGame success/death sprite
    EndOfGame endOfGameMessage; // visuals for endOfGame success/death message
    sf::Font pokemonhollow;     // visuals for score
    sf::Text textscore;
    sf::RectangleShape dimOverlay; // grey overlay for menu

    // METHODS
    void updateHealth();                         // update health of player
    void endOfGame(int pSuccess, int pGamemode); // success/death screen
    void checkPositions();                       // checks whether any objects spawned on top of each other

    template <typename T, typename U> // templates and methods for checking overlap between two groups
    void checkOverlap(T &group1, U &group2, int size1, int size2, int &done);
    template <typename U>
    void checkOverlapP(Player &player, U &group1, int size1, int &done);
    template <typename T>
    void checkOverlapPC(PokeCenter &pokeCenter, T &group1, int size1, int &done);
    void setNewPosition(sf::Sprite &entity);

    void changeGamemode(int pGamemode); // changes gamemode

public:
    // VARIABLES
    int moves;                  // counts amount of moves player did before finishing
    int direction;              // saves in which direction the player is moving
    int playerPosX, playerPosY; // saves position of player (X & Y)
    bool menuIsOpen;            // saves whether menu is open
    bool prevMenuKeyPressed;    // saves whether menu key was pressed in previous frame
    int positionCX[3];          // IMPORTANT: same number as collectables array size and positionCY
    int positionCY[3];          // IMPORTANT: same number as collectables array size and positionCX
    int gamemode;               // 0 = Normal, 1 = Survival

    // OBJECTS
    sf::Time InputDelay = sf::seconds(0.0001f); // input delay, added for smooth movement
    sf::Clock InputDelayTimer;                  // timer, added for smooth movement

    Player player;

    // amount of each object (trainers, Pokeballs, Pokemon, trees), reduce any to lower difficulty (and vice versa)
    Collectable collectables[3]; // IMPORTANT: same number as positionCX and positionCY
    Trainer trainers[4];
    Pokeball pokeballs[5];
    Obstacle trees[3];

    Obstacle mountainTopRight;
    Obstacle mountainTopLeft;

    sf::RenderWindow *window_field; // field is realised as renderwindow
    sf::Sprite spritef;             // visuals for field

    HealthBar healthbar;
    PokeBox pokebox;
    PokeCenter pokecenter;
    Menu menu;

    sf::Clock realTimeClock;
    float elapsedTime = 0.0f;
    sf::Text timescore;

    // METHODS
    Field();  // constructor
    ~Field(); // destructor

    void checkCollision(); // checks for any collision between sprites on the field
    void resetGame();      // resets the game

    void openMenu();                                                         // opens the menu
    void closeMenu();                                                        // closes the menu
    void drawMenu();                                                         // draws the menu
    void handleSliderMovement(RectangleShape &pSliderHandle, Event &pEvent); // handles slider movement in menu
    void handleButtonEvents(RectangleShape &pButton, Event &pEvent);         // handles button events in menu

    const bool getFieldIsOpen() const; // get whether the field is still opened
};

#endif
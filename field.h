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
    Class that is used to create the gamefield
*/

class Field
{
    
    private:
    // variables
    int moves;
    int score;
    int direction;
    int playerPosX, playerPosY;
    int amountOfTrees;

    sf::Time InputDelay = sf::seconds(0.0001f);
    sf::Clock InputDelayTimer;

    sf::Sound collected, failure, win, damage;
    sf::SoundBuffer bufferC,bufferF,bufferW, bufferD;

    //amount of each object (Trainers, Pokeballs, Pokemon, Trees), reduce any to lower difficulty and vice versa
    Player player;
    Enemy enemies[4];
    Enemy2 pokeballs[5];
    Collectable collectables[3];    //IMPORTANT: same number as in two lines below
    int positionCX[3];              //IMPORTANT: same number as in line below/line above
    int positionCY[3];              //IMPORTANT: same number as in two lines above
    sf::Sprite spriteTree[6];       //IMPORTANT: this number is the sum of amount of trees and amount of transparent rectangles. Maybe implement vector here.
    sf::Texture textureTree[6];     //IMPORTANT: this number is the sum of amount of trees and amount of transparent rectangles. Maybe implement vector here.

    sf::Sprite spriteCPB;
    sf::Texture textureCPB;
    
    sf::Sprite spriteHP;
    sf::Texture textureHP;

    sf::Sprite spritePC;
    sf::Texture texturePC;

    sf::Sprite spritef;
    sf::Texture texturef;

    sf::Sprite spriteDS;
    sf::Texture textureDS;

    sf::Sprite spriteDM;
    sf::Texture textureDM;

    sf::Sprite spriteSS;
    sf::Texture textureSS;

    sf::Sprite spriteSM;
    sf::Texture textureSM;

    sf::Font pokemonhollow;
    sf::Text scoretext;


    void checkCollision();
    void updateHealth();
    void resetGame();
    void checkPositions();
    void checkForWin();
    void pokeballMovement();

    public:

    //variables
    sf::RenderWindow* field;

    //Constructors / Destructors
    Field();
    ~Field();

    //public Functions
    void update(); // update the game data
    void render();
    //GET
    const bool getFieldIsOpen() const;
    

};

#endif

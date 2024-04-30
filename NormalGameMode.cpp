#include "NormalGameMode.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono> //include all necessary external files

NormalGameMode::NormalGameMode(Field *pField) // constructor
{
    std::cout << "NormalGameMode constructor" << std::endl;
    field = pField;
}

NormalGameMode::~NormalGameMode() // destructor
{
}

void NormalGameMode::update() // manages all the game data
{
    field->playerPosX = field->player.sprite.getPosition().x; // save current player x position
    field->playerPosY = field->player.sprite.getPosition().y; // save current player y position

    int movement, speed;
    movement = field->playerPosY + field->playerPosX; // walking animation, as long as speed is odd
    speed = field->player.getSpeed();

    sf::Event event;

    while (field->window_field->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            field->window_field->close();
        }
        // handle menu buttons and sliders
        field->handleSliderMovement(field->menu.sliderhandle_volume, event);
        field->handleButtonEvents(field->menu.button_mode1, event);
        field->handleButtonEvents(field->menu.button_mode2, event);
        field->handleButtonEvents(field->menu.button_difficulty1, event);
        field->handleButtonEvents(field->menu.button_difficulty2, event);
        field->handleButtonEvents(field->menu.button_difficulty3, event);
    }

    bool currentMenuKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::M);

    if (field->InputDelayTimer.getElapsedTime() > field->InputDelay) // if a certain input delay has passed
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || (sf::Keyboard::isKeyPressed(sf::Keyboard::M)))))
        { // and if any of the used keys is pressed
            // CLOSE/RESET/MENU
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // if "Esc" is pressed
            {
                field->window_field->close(); // close everything
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // if "R" is pressed
            {
                field->resetGame(); // reset the game
            }

            // MENU
            if (currentMenuKeyPressed && !field->prevMenuKeyPressed)
            {
                // open menu if its closed, close it if its open at the moment
                if (field->menuIsOpen == false)
                {
                    field->openMenu();
                    field->menuIsOpen = true;
                }
                else
                {
                    field->closeMenu();
                    field->menuIsOpen = false;
                }

                field->InputDelayTimer.restart(); // restart the cooldown timer after opening or closing the menu
            }

            if (field->menuIsOpen == false)
            {
                // WASD MOVEMENT
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    field->direction = 0;                                                                   // current direction: up
                    field->player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png"); // alternate between the two animation frames
                    field->playerPosY -= speed;                                                             // move player up
                    field->moves++;                                                                         // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    field->direction = 1;                                                                       // current direction: left
                    field->player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png"); // alternate between the two animation frames
                    field->playerPosX -= speed;                                                                 // move player to the left
                    field->moves++;                                                                             // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    field->direction = 2;                                                                       // current direction: down
                    field->player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png"); // alternate between the two animation frames
                    field->playerPosY += speed;                                                                 // move player down
                    field->moves++;                                                                             // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    field->direction = 3;                                                                       // current direction: right
                    field->player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 6) + ".png"); // alternate between the two animation frames
                    field->playerPosX += speed;                                                                 // move player right
                    field->moves++;                                                                             // player has done a move
                }

                field->InputDelayTimer.restart(); // restart input delay timer
            }
        }

        // Window borders - keeping the player half its size away from any edges of the field
        if (field->playerPosX < (field->player.sprite.getTexture()->getSize().x) / 2)
        {
            field->playerPosX = (field->player.sprite.getTexture()->getSize().x) / 2;
        }
        if (field->playerPosX > (int)field->window_field->getSize().x - (field->player.sprite.getTexture()->getSize().x) / 2)
        {
            field->playerPosX = field->window_field->getSize().x - (field->player.sprite.getTexture()->getSize().x) / 2;
        }
        if (field->playerPosY < (field->player.sprite.getTexture()->getSize().y) / 2)
        {
            field->playerPosY = (field->player.sprite.getTexture()->getSize().y) / 2;
        }
        if (field->playerPosY > 920 - (field->player.sprite.getTexture()->getSize().y) / 2)
        {
            field->playerPosY = 920 - (field->player.sprite.getTexture()->getSize().y) / 2;
        }

        field->player.sprite.setPosition(field->playerPosX, field->playerPosY); // set player sprite to updated position
        field->player.shapeP.setPosition(field->playerPosX, field->playerPosY); // set player shape  to updated position
    }

    field->prevMenuKeyPressed = currentMenuKeyPressed; // important for menu display, so that it doesn't open and close immediately
}

void NormalGameMode::render() // displays the game field
{
    field->window_field->clear(); // clear last frame

    // DRAW ALL ENTITIES
    field->window_field->draw(field->spritef);
    field->window_field->draw(field->healthbar.sprite);
    field->window_field->draw(field->pokebox.sprite);
    field->window_field->draw(field->pokecenter.sprite);

    for (int i = 0; i < (sizeof(field->trainers) / sizeof(field->trainers[0])); i++) // for all trainers
    {
        field->window_field->draw(field->trainers[i].sprite);
    }

    for (int i = 0; i < (sizeof(field->collectables) / sizeof(field->collectables[0])); i++) // for all Pokemon
    {
        field->window_field->draw(field->collectables[i].sprite);

        if (!(field->collectables[i].sprite.getGlobalBounds().intersects(field->pokebox.sprite.getGlobalBounds()))) // if collectable is not intersecting with the collected Pokemon box
        {
            field->positionCX[i] = field->collectables[i].sprite.getPosition().x; // save its X position in a variable (used for resetting game)
            field->positionCY[i] = field->collectables[i].sprite.getPosition().y; // save its Y position in a variable (used for resetting game)
        }
    }

    for (int i = 0; i < (sizeof(field->pokeballs) / sizeof(field->pokeballs[0])); i++) // for all Pokeballs
    {
        field->window_field->draw(field->pokeballs[i].sprite);
    }

    for (int i = 0; i < (sizeof(field->trees) / sizeof(field->trees[0])); i++) // for all trees
    {
        field->window_field->draw(field->trees[i].sprite);
    }

    field->window_field->draw(field->mountainTopLeft.sprite);
    field->window_field->draw(field->mountainTopRight.sprite);

    if (field->menuIsOpen == false)
    {
        pokeballMovement();      // moving Pokeballs
        field->checkCollision(); // checking for any sort of player - entity collision
    }

    field->window_field->draw(field->player.sprite);

    if (field->menuIsOpen == true)
    {
        field->drawMenu(); // draw menu
    }

    field->window_field->display(); // display updated frame
}

void NormalGameMode::pokeballMovement()
{
    for (int i = 0; i < (sizeof(field->pokeballs) / sizeof(field->pokeballs[0])); i++) // for all pokeballs
    {
        field->pokeballs[i].sprite.setPosition(((field->pokeballs[i].sprite.getPosition().x) - field->pokeballs[i].speed), field->pokeballs[i].sprite.getPosition().y); // move Pokeball to the left (by an amount depending on its speed)

        if (field->pokeballs[i].sprite.getPosition().x <= -100) // if Pokeball has passed the left screen border
        {
            field->pokeballs[i].speed = field->pokeballs[i].giveRandomDouble(7.5, 9.5); // select new random speed
            int newPosY;
            newPosY = field->pokeballs[i].giveRandomNumber(0, 900); // select new random spawn height
            field->pokeballs[i].sprite.setPosition(1970, newPosY);  // set Pokeball position to the right of the screen at selected height
        }
    }
}

#include "SurvivalGameMode.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono> //include all necessary external files

SurvivalGameMode::SurvivalGameMode(Field *pField) // constructor
{
    std::cout << "SurvivalGameMode constructor" << std::endl;
    field = pField;
}

SurvivalGameMode::~SurvivalGameMode()
{
}

void SurvivalGameMode::update() // manages all the game data
{

    if (!field->menuIsOpen)
    {
        field->elapsedTime += field->realTimeClock.restart().asSeconds(); // update the elapsed time
    }
    else
    {
        field->realTimeClock.restart(); // pause if menu is open
    }

    field->timescore.setString("Time: " + std::to_string(static_cast<int>(field->elapsedTime)) + "." + std::to_string(static_cast<int>((field->elapsedTime - static_cast<int>(field->elapsedTime)) * 10)) + " s"); // set timescore

    field->playerPosX = field->player.sprite.getPosition().x; // save current player x position
    field->playerPosY = field->player.sprite.getPosition().y; // save current player y position

    int movement, speed;
    movement = field->playerPosY + field->playerPosX; // walking animation, as long as speed is odd
    speed = field->player.getSpeed();                 // receives player speed as initialized in player.cpp

    sf::Event event;

    while (field->window_field->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            field->window_field->close();
        }
        // handle slider movement and button events
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
                resetGame(); // reset the game
            }

            // MENU
            if (currentMenuKeyPressed && !field->prevMenuKeyPressed)
            {
                if (field->menuIsOpen == false)
                {
                    field->openMenu(); // open the menu
                    field->menuIsOpen = true;
                }
                else
                {
                    field->closeMenu(); // close the menu
                    field->menuIsOpen = false;
                }

                field->InputDelayTimer.restart(); // Restart the cooldown timer after opening or closing the menu.
            }

            if (field->menuIsOpen == false)
            {
                // WASD MOVEMENT
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // if "W" is pressed
                {
                    field->direction = 0;                                                                   // current direction: up
                    field->player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png"); // alternate between the two animation frames
                    field->playerPosY -= speed;                                                             // move player up
                    field->moves++;                                                                         // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // if "A" is pressed
                {
                    field->direction = 1;                                                                       // current direction: left
                    field->player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png"); // alternate between the two animation frames
                    field->playerPosX -= speed;                                                                 // move player to the left
                    field->moves++;                                                                             // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // if "S" is pressed
                {
                    field->direction = 2;                                                                       // current direction: down
                    field->player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png"); // alternate between the two animation frames
                    field->playerPosY += speed;                                                                 // move player down
                    field->moves++;                                                                             // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // if "D" is pressed
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

    field->prevMenuKeyPressed = currentMenuKeyPressed;
}

void SurvivalGameMode::render() // displays the game field
{
    field->window_field->clear(); // clear last frame

    // DRAW ALL ENTITIES
    field->window_field->draw(field->spritef);
    field->window_field->draw(field->healthbar.sprite);

    field->window_field->draw(field->timescore);

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

void SurvivalGameMode::pokeballMovement()
{
    for (int i = 0; i < (sizeof(field->pokeballs) / sizeof(field->pokeballs[0])); i++) // for all Pokeballs
    {
        field->pokeballs[i].sprite.setPosition(((field->pokeballs[i].sprite.getPosition().x) - field->pokeballs[i].speed), field->pokeballs[i].sprite.getPosition().y); // move Pokeball to the left (by an amount depending on its speed)

        if (field->pokeballs[i].sprite.getPosition().x <= -100) // if Pokeball has passed the left screen border
        {
            field->pokeballs[i].speed = field->pokeballs[i].giveRandomDouble(7.5, 9.5); // select new random speed
            int newPosY;
            newPosY = field->pokeballs[i].giveRandomNumberWithoutSpawnProof(0, 900); // select new random spawn height, no spawn proof
            field->pokeballs[i].sprite.setPosition(1970, newPosY);                   // set Pokeball position to the right of the screen at selected height
        }
    }
}

void SurvivalGameMode::resetGame()
{
    field->elapsedTime = 0; // reset timer
    field->realTimeClock.restart();

    field->timescore.setString("Time: 0.0 s"); // reset timescore
    field->timescore.setCharacterSize(65);
    field->timescore.setFillColor(sf::Color::White);
    field->timescore.setPosition(sf::Vector2f(100, 960));

    field->player.setHealthPoints(3);                          // reset HP
    field->healthbar.setTexture("resources/health_bar_3.png"); // load health bar with 3 HP
    field->window_field->draw(field->healthbar.sprite);

    field->playerPosX = field->window_field->getSize().x / 2; // reset player position (X)
    field->playerPosY = field->window_field->getSize().y / 2; // reset player position (Y)
    field->window_field->draw(field->player.sprite);
}

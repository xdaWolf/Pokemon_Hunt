#include "Field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono> //include all necessary external files

Field::Field()
{
    std::cout << "Field constructor" << std::endl;

    // SET VISUALS - FIELD
    // field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen); // open a full-screen window called "Pokemon-Hunt"
    field = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Pokemon-Hunt"); // open a 1920x1080 window called "Pokemon-Hunt", IMPORTANT: only use this if upper method doesn't work properly on your device (for example if secondary monitor is used)
    field->setFramerateLimit(60);                                            // don't exceed a framerate of 60fps
    texturef.loadFromFile("resources/backgroundv3.png");                     // load background image
    texturef.setSmooth(true);
    spritef.setTexture(texturef);                                                        // set field sprite to background image
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2, texturef.getSize().y / 2)); // move origin of sprite (default: top left) to center of sprite
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));   // place background sprite in the middle of the screen
    dimOverlay.setSize(sf::Vector2f(field->getSize().x, field->getSize().y));            // create a rectangle with the size of the screen
    dimOverlay.setFillColor(sf::Color(0, 0, 0, 150));                                    // set colour of rectangle to transparent

    // SET VARIABLES - SOUND
    bufferC.loadFromFile("resources/collected.wav"); // load sound effects
    bufferW.loadFromFile("resources/win.wav");
    bufferF.loadFromFile("resources/failure.wav");
    bufferD.loadFromFile("resources/damage.wav");
    collected.setBuffer(bufferC); // set buffer for each sound effect
    win.setBuffer(bufferW);
    failure.setBuffer(bufferF);
    damage.setBuffer(bufferD);
    collected.setVolume(70); // set volume for each sound effect
    win.setVolume(55);
    failure.setVolume(25);
    damage.setVolume(35);

    // SET VISUALS - TREES
    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees
    {
        trees[i].setTexture("resources/tree_" + std::to_string(trees[0].giveRandomNumber(1, 1)) + ".png");
        trees[i].initializeSpriteAndTexture();
    }
    mountainTopLeft.setTexture("resources/mountainTopLeft.png");
    mountainTopLeft.initializeSpriteAndTexture();                  // load mountainTopLeft image
    mountainTopLeft.sprite.setPosition(48, 99);                    // set position of mountainTopLeft
    mountainTopRight.setTexture("resources/mountainTopRight.png"); // load mountainTopRight image
    mountainTopRight.initializeSpriteAndTexture();                 // initialize mountainTopRight
    mountainTopRight.sprite.setPosition(1590, 72);                 // set position of mountainTopRight

    moves = 0;        // initialize the moves variable which is used for the score calculation
    checkPositions(); // check whether entities tried to spawn on one another when they weren't supposed to
    menuIsOpen = false;
    prevMenuKeyPressed = false;
}

Field::~Field() // destructor
{
    std::cout << "Field destructor" << std::endl;
    delete field; // delete the field
}

const bool Field::getFieldIsOpen() const // returns whether field is open
{
    return field->isOpen();
}

const bool Field::getMenuIsOpen() const // returns if menu is open
{
    return menuIsOpen;
}

void Field::update() // manages all the game data
{
    playerPosX = player.sprite.getPosition().x; // save current player x position
    playerPosY = player.sprite.getPosition().y; // save current player y position

    int movement, speed;
    movement = playerPosY + playerPosX; // walking animation, as long as speed is odd
    speed = player.getSpeed();          // receives player speed as initialized in player.cpp

    sf::Event event;

    while (field->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            field->close();
        }
        // Weitere Verarbeitung von Ereignissen je nach Bedarf
    }

    bool currentMenuKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::M);

    if (InputDelayTimer.getElapsedTime() > InputDelay) // if a certain input delay has passed
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || (sf::Keyboard::isKeyPressed(sf::Keyboard::M)))))
        { // and if any of the 6 used keys is pressed
            // CLOSE/RESET/MENU
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // if "Esc" is pressed
            {
                field->close(); // close everything
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // if "R" is pressed
            {
                resetGame(); // reset the game
            }

            // MENU
            if (currentMenuKeyPressed && !prevMenuKeyPressed)
            {
                if (menuIsOpen == false)
                {
                    openMenu(); // open the menu
                    menuIsOpen = true;
                }
                else
                {
                    closeMenu(); // close the menu
                    menuIsOpen = false;
                }

                InputDelayTimer.restart(); // Restart the cooldown timer after opening or closing the menu.
            }

            if (menuIsOpen == false)
            {
                // WASD MOVEMENT
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // if "W" is pressed
                {
                    direction = 0;                                                                   // current direction: up
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png"); // alternate between the two animation frames
                    playerPosY -= speed;                                                             // move player up
                    moves++;                                                                         // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // if "A" is pressed
                {
                    direction = 1;                                                                       // current direction: left
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png"); // alternate between the two animation frames
                    playerPosX -= speed;                                                                 // move player to the left
                    moves++;                                                                             // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // if "S" is pressed
                {
                    direction = 2;                                                                       // current direction: down
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png"); // alternate between the two animation frames
                    playerPosY += speed;                                                                 // move player down
                    moves++;                                                                             // player has done a move
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // if "D" is pressed
                {
                    direction = 3;                                                                       // current direction: right
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 6) + ".png"); // alternate between the two animation frames
                    playerPosX += speed;                                                                 // move player right
                    moves++;                                                                             // player has done a move
                }

                InputDelayTimer.restart(); // restart input delay timer
            }
        }

        // Window borders - keeping the player half its size away from any edges of the field
        if (playerPosX < (player.sprite.getTexture()->getSize().x) / 2)
        {
            playerPosX = (player.sprite.getTexture()->getSize().x) / 2;
        }
        if (playerPosX > (int)field->getSize().x - (player.sprite.getTexture()->getSize().x) / 2)
        {
            playerPosX = field->getSize().x - (player.sprite.getTexture()->getSize().x) / 2;
        }
        if (playerPosY < (player.sprite.getTexture()->getSize().y) / 2)
        {
            playerPosY = (player.sprite.getTexture()->getSize().y) / 2;
        }
        if (playerPosY > 920 - (player.sprite.getTexture()->getSize().y) / 2)
        {
            playerPosY = 920 - (player.sprite.getTexture()->getSize().y) / 2;
        }

        player.sprite.setPosition(playerPosX, playerPosY); // set player sprite to updated position
        player.shapeP.setPosition(playerPosX, playerPosY); // set player shape  to updated position
    }

    prevMenuKeyPressed = currentMenuKeyPressed;
}

void Field::render() // displays the game field
{
    field->clear(); // clear last frame

    // DRAW ALL ENTITIES
    field->draw(spritef);
    field->draw(healthbar.sprite);
    field->draw(pokebox.sprite);
    field->draw(pokecenter.sprite);

    for (int i = 0; i < (sizeof(trainers) / sizeof(trainers[0])); i++) // for all trainers
    {
        field->draw(trainers[i].sprite);
    }

    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        field->draw(collectables[i].sprite);

        if (!(collectables[i].sprite.getGlobalBounds().intersects(pokebox.sprite.getGlobalBounds()))) // if collectable is not intersecting with the collected Pokemon box
        {
            positionCX[i] = collectables[i].sprite.getPosition().x; // save its X position in a variable (used for resetting game)
            positionCY[i] = collectables[i].sprite.getPosition().y; // save its Y position in a variable (used for resetting game)
        }
    }

    for (int i = 0; i < (sizeof(pokeballs) / sizeof(pokeballs[0])); i++) // for all Pokeballs
    {
        field->draw(pokeballs[i].sprite);
    }

    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees
    {
        field->draw(trees[i].sprite);
    }

    field->draw(mountainTopLeft.sprite);
    field->draw(mountainTopRight.sprite);

    if (menuIsOpen == false)
    {
        pokeballMovement(); // moving Pokeballs
        checkCollision();   // checking for any sort of player - entity collision
    }

    field->draw(player.sprite);

    if (menuIsOpen == true)
    {
        field->draw(dimOverlay);
        field->draw(menu.sprite);
    }

    field->display(); // display updated frame
}

void Field::pokeballMovement()
{
    for (int i = 0; i < (sizeof(pokeballs) / sizeof(pokeballs[0])); i++)
    {                                                                                                                                       // for all Pokeballs
        pokeballs[i].sprite.setPosition(((pokeballs[i].sprite.getPosition().x) - pokeballs[i].speed), pokeballs[i].sprite.getPosition().y); // move Pokeball to the left (by an amount depending on its speed)

        if (pokeballs[i].sprite.getPosition().x <= -100) // if Pokeball has passed the left screen border
        {
            pokeballs[i].speed = pokeballs[i].giveRandomDouble(7.5, 9.5); // select new random speed
            int newPosY;
            newPosY = pokeballs[i].giveRandomNumber(0, 900); // select new random spawn height
            pokeballs[i].sprite.setPosition(1970, newPosY);  // set Pokeball position to the right of the screen at selected height
        }
    }
}

void Field::checkCollision()
{
    for (int i = 0; i < (sizeof(trainers) / sizeof(trainers[0])); i++) // for all trainers
    {
        if (player.sprite.getGlobalBounds().intersects(trainers[i].sprite.getGlobalBounds())) // if player touches trainer
        {
            std::cout << "Player hit trainer" << std::endl;
            player.setHealthPoints(player.getHealthPoints() - 1); // reduce HP by 1
            std::cout << "Player has " << player.getHealthPoints() << " HP left" << std::endl;
            player.sprite.setPosition(sf::Vector2f(player.spawnPX, player.spawnPY)); // reset player sprite position
            player.shapeP.setPosition(sf::Vector2f(player.spawnPX, player.spawnPY)); // reset player shape  position
            updateHealth();                                                          // update health
        }
    }

    for (int i = 0; i < (sizeof(pokeballs) / sizeof(pokeballs[0])); i++) // for all Pokeballs
    {
        if (player.sprite.getGlobalBounds().intersects(pokeballs[i].sprite.getGlobalBounds())) // if player touches Pokeball
        {
            std::cout << "Player hit Pokeball" << std::endl;
            player.setHealthPoints(player.getHealthPoints() - 1); // reduce HP by 1
            std::cout << "Player has " << player.getHealthPoints() << " HP left" << std::endl;
            player.sprite.setPosition(sf::Vector2f(player.spawnPX, player.spawnPY)); // reset player sprite position
            player.shapeP.setPosition(sf::Vector2f(player.spawnPX, player.spawnPY)); // reset player shape  position
            updateHealth();                                                          // update health
        }
    }

    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        if (player.sprite.getGlobalBounds().intersects(collectables[i].sprite.getGlobalBounds())) // if player touches Pokemon
        {
            std::cout << "Player collected Pokemon" << std::endl;
            player.setCollected(player.getCollected() + 1); // increase amount of collected Pokemon by 1
            std::cout << "Player has collected " << player.getCollected() << " Pokemon" << std::endl;
            collectables[i].sprite.setScale(0.5, 0.5); // shrink collected Pokemon
            collected.play();                          // play sound effect for collecting Pokemon

            if ((sizeof(collectables) / sizeof(collectables[0])) > 1) // if there are 2 or more Pokemon
            {
                collectables[i].sprite.setPosition(115 + (271 / ((sizeof(collectables) / sizeof(collectables[0])) - 1) * (player.getCollected() - 1)), 1020); // move collected Pokemon to the CPB. The rather complex calculation makes any amount of collectables possible.
                // 92  = spriteCPB.getPosition().x - textureCPB.getSize().x / 2 + 25                                                                     //explains the origin of the "92"  above in case a different sized CPB is needed
                // 271 = spriteCPB.getPosition().x + textureCPB.getSize().x / 2 - 25 - collectables[i].getTexture().x - (92)                             //explains the origin of the "271" above in case a different sized CPB is needed
            }
            else // if there's only 1 Pokemon
            {
                collectables[i].sprite.setPosition(pokebox.sprite.getPosition().x - collectables[i].sprite.getTexture()->getSize().x / 2, 1000); // place it in the center of the CPB
            }
        }
    }

    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees
    {
        while (player.sprite.getGlobalBounds().intersects(trees[i].sprite.getGlobalBounds())) // as long as player is within the tree
        {
            switch (direction)
            {                 // note: moving the player one pixel at a time here to prevent the feeling of false hitboxes
            case 0:           // if direction is up
                playerPosY++; // move player down
                break;
            case 1:           // if direction is left
                playerPosX++; // move player to the right
                break;
            case 2:           // if direction is down
                playerPosY--; // move player up
                break;
            case 3:           // if direction is right
                playerPosX--; // move player to the left
                break;
            }
            player.sprite.setPosition(playerPosX, playerPosY); // set new player position
        }
    }

    while (player.sprite.getGlobalBounds().intersects(mountainTopLeft.sprite.getGlobalBounds()) || player.sprite.getGlobalBounds().intersects(mountainTopRight.sprite.getGlobalBounds())) // if player touches mountainTopLeft
    {
        switch (direction)
        {                 // note: moving the player one pixel at a time here to prevent the feeling of false hitboxes
        case 0:           // if direction is up
            playerPosY++; // move player down
            break;
        case 1:           // if direction is left
            playerPosX++; // move player to the right
            break;
        case 2:           // if direction is down
            playerPosY--; // move player up
            break;
        case 3:           // if direction is right
            playerPosX--; // move player to the left
            break;
        }
        player.sprite.setPosition(playerPosX, playerPosY); // set new player position
    }

    if (player.sprite.getGlobalBounds().intersects(pokecenter.sprite.getGlobalBounds())) // if player touches PokeCenter
    {
        if (player.getCollected() >= sizeof(collectables) / sizeof(collectables[0])) // if player has collected all Pokemon
        {
            std::cout << "Player wins" << std::endl;
            win.play(); // play sound effect for winning the game

            score = (1150 - moves) / (4 - player.getHealthPoints()); // calculate score based on moves made & HP left
            // note: you need around 150 moves minimum to get from spawn to PokeCenter, thus, the highest possible score is ~1000
            if (score < 100) // if player scores less than 100 points
            {
                score = 100; // award him with 100 points anyways to keep a feeling of success (:
            }
            std::cout << "Score: " << score << std::endl;

            pokemonhollow.loadFromFile("resources/pokemon_hollow.ttf");       // load pokemon font
            textscore.setFont(pokemonhollow);                                 // use loaded font
            textscore.setString("Score: " + std::to_string(score));           // print score on screen
            textscore.setCharacterSize(96);                                   // set size of score
            textscore.setFillColor(sf::Color::Black);                         // set colour of score
            textscore.setPosition(sf::Vector2f(100, field->getSize().y / 4)); // set position of score

            success = 1;        // player did win
            endOfGame(success); // show success screen
        }
    }
}

void Field::updateHealth()
{
    damage.play();              // play sound effect for getting damaged
    for (int i = 0; i < 3; i++) // for 3 iterations
    {
        if (i % 2 == 0) // alternate between...
        {
            player.shapeP.setFillColor(sf::Color::Red); // player turns red
        }
        else if (i % 2 != 0) //...and...
        {
            player.shapeP.setFillColor(sf::Color::Transparent); // player turns invisible
        }
        field->draw(player.shapeP); // draw player shape
        field->display();           // display updated frame
        Sleep(100);                 // wait 0.1s
    }

    if (player.getHealthPoints() == 2) // if remaining HP = 2
    {
        healthbar.setTexture("resources/health_bar_2.png"); // load health bar with 2 HP
    }
    else if (player.getHealthPoints() == 1) // if remaining HP = 1
    {
        healthbar.setTexture("resources/health_bar_1.png"); // load health bar with 1 HP
    }
    else if (player.getHealthPoints() == 0) // if remaining HP = 0
    {
        healthbar.setTexture("resources/health_bar_0.png"); // load health bar with 2 HP

        std::cout << "Player lost" << std::endl;
        failure.play(); // play sound effect for losing the game

        success = 0;        // player didn't win
        endOfGame(success); // show death screen
    }
}

void Field::openMenu()
{
    dimOverlay.setFillColor(sf::Color(0, 0, 0, 150));
    field->draw(dimOverlay); // draw rectangle
    menu.sprite.setPosition(960, 540);
    field->draw(menu.sprite); // draw menu
}

void Field::closeMenu()
{
    menu.sprite.setPosition(sf::Vector2f(-1000, -1000)); // set position out of view to "destroy" it
    field->draw(menu.sprite);                            // draw menu
    dimOverlay.setFillColor(sf::Color::Transparent);     // set colour of rectangle to transparent
    field->draw(dimOverlay);                             // draw rectangle
}

void Field::endOfGame(int pSuccess)
{
    field->clear(); // clear last frame

    if (pSuccess) // if player won
    {
        endOfGameSprite.setTexture("resources/success_sprite.png");
        endOfGameMessage.setTexture("resources/success_message.png");
        endOfGameMessage.initializeSpriteAndTexture();
        endOfGameSprite.initializeSpriteAndTexture();
    }
    else // otherwise
    {
        endOfGameSprite.setTexture("resources/death_sprite.png");
        endOfGameMessage.setTexture("resources/death_message.png");
        endOfGameMessage.initializeSpriteAndTexture();
        endOfGameSprite.initializeSpriteAndTexture();
    }

    endOfGameSprite.sprite.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 3));      // set position for success/death sprite
    endOfGameMessage.sprite.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 4 * 3)); // set position for success/death message

    // DRAW ALL ENTITIES OF ENDOFGAME SCREEN
    field->draw(spritef);
    field->draw(pokecenter.sprite);
    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees (excluding invisible mountain rectangles)
    {
        field->draw(trees[i].sprite);
    }
    field->draw(mountainTopLeft.sprite);
    field->draw(mountainTopRight.sprite);
    field->draw(healthbar.sprite);
    if (pSuccess)
    {
        field->draw(textscore);
    } // only draw score if player won
    field->draw(endOfGameSprite.sprite);
    field->draw(endOfGameMessage.sprite);

    field->display(); // display updated frame

    while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
    } // wait until player resets or quits

    resetGame(); // reset the game
}

void Field::resetGame()
{
    player.setHealthPoints(3);                          // reset HP
    player.setCollected(0);                             // reset amount of collected Pokemon
    moves = 0;                                          // reset move counter
    healthbar.setTexture("resources/health_bar_3.png"); // load health bar with 3 HP
    field->draw(healthbar.sprite);
    playerPosX = player.spawnPX; // reset player position (X)
    playerPosY = player.spawnPY; // reset player position (Y)
    field->draw(player.sprite);
    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        if (collectables[i].sprite.getGlobalBounds().intersects(pokebox.sprite.getGlobalBounds())) // if Pokemon was collected before / is placed on the CPB
        {
            collectables[i].sprite.setScale(1, 1); // enlarge Pokemon to original size
        }
        collectables[i].sprite.setPosition(positionCX[i], positionCY[i]); // place Pokemon at original spawn position
    }
}

void Field::checkPositions() // note: superiority: PokeCenter/player > trees > trainers/Pokemon - lower superiority changes position in case of an overlap. Revise this in the future to get rid of the redundancies.
{
    int done = 0; // checks whether all entities spawned in distinct positions

    // PLAYER x POKEMON
    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        if (player.sprite.getGlobalBounds().intersects(collectables[i].sprite.getGlobalBounds())) // if Pokemon spawned on player
        {
            std::cout << "P x C, ";
            int newPosX, newPosY;
            newPosX = collectables[i].giveRandomNumber(0, 1920);  // select new random x position for Pokemon
            newPosY = collectables[i].giveRandomNumber(0, 900);   // select new random y position for Pokemon
            collectables[i].sprite.setPosition(newPosX, newPosY); // set new position
            field->draw(collectables[i].sprite);
            done++;
        }
    }

    // PLAYER x ENEMY
    for (int i = 0; i < (sizeof(trainers) / sizeof(trainers[0])); i++) // for all trainers
    {
        if (player.sprite.getGlobalBounds().intersects(trainers[i].sprite.getGlobalBounds())) // if trainer spawned on player
        {
            std::cout << "P x E, ";
            int newPosX, newPosY;
            newPosX = trainers[i].giveRandomNumber(0, 1920);  // select new random x position for trainer
            newPosY = trainers[i].giveRandomNumber(0, 900);   // select new random y position for trainer
            trainers[i].sprite.setPosition(newPosX, newPosY); // set new position
            field->draw(trainers[i].sprite);
            done++;
        }
    }

    // PLAYER x TREE
    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees (excluding invisible mountain rectangles)
    {
        if (player.sprite.getGlobalBounds().intersects(trees[i].sprite.getGlobalBounds())) // if tree spawned on player
        {
            std::cout << "P x T, ";
            int newPosX, newPosY;
            newPosX = trainers[0].giveRandomNumber(0, 1920); // select new random x position for tree
            newPosY = trainers[0].giveRandomNumber(0, 900);  // select new random y position for tree
            trees[i].sprite.setPosition(newPosX, newPosY);   // set new position
            field->draw(trees[i].sprite);
            done++;
        }
    }

    // COLLECTABLE x COLLECTABLE
    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        for (int k = i + 1; k < (sizeof(collectables) / sizeof(collectables[0])); k++) // for all other Pokemon
        {
            if (collectables[i].sprite.getGlobalBounds().intersects(collectables[k].sprite.getGlobalBounds())) // if Pokemon spawned on another Pokemon
            {
                std::cout << "C x C, ";
                int newPosX, newPosY;
                newPosX = collectables[i].giveRandomNumber(0, 1920);  // select new random x position for Pokemon
                newPosY = collectables[i].giveRandomNumber(0, 900);   // select new random y position for Pokemon
                collectables[i].sprite.setPosition(newPosX, newPosY); // set new position
                field->draw(collectables[i].sprite);
                done += 1;
            }
        }
    }

    // COLLECTABLE x ENEMY
    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        for (int k = 0; k < (sizeof(trainers) / sizeof(trainers[0])); k++) // for all trainers
        {
            if (collectables[i].sprite.getGlobalBounds().intersects(trainers[k].sprite.getGlobalBounds())) // if Pokemon spawned on trainer
            {
                std::cout << "C x E, ";
                int newPosX, newPosY;
                newPosX = collectables[i].giveRandomNumber(0, 1920);  // select new random x position for Pokemon
                newPosY = collectables[i].giveRandomNumber(0, 900);   // select new random y position for Pokemon
                collectables[i].sprite.setPosition(newPosX, newPosY); // set new position
                field->draw(collectables[i].sprite);
                done += 1;
            }
        }
    }

    // COLLECTABLE x TREE
    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees (including invisible mountain rectangles)
    {
        for (int k = 0; k < (sizeof(collectables) / sizeof(collectables[0])); k++) // for all Pokemon
        {
            if (trees[i].sprite.getGlobalBounds().intersects(collectables[k].sprite.getGlobalBounds())) // if Pokemon spawned on tree
            {
                std::cout << "C x T, ";
                int newPosX, newPosY;
                newPosX = collectables[k].giveRandomNumber(0, 1920);  // select new random x position for Pokemon
                newPosY = collectables[k].giveRandomNumber(0, 900);   // select new random y position for Pokemon
                collectables[k].sprite.setPosition(newPosX, newPosY); // set new position
                field->draw(collectables[k].sprite);
                done += 1;
            }
        }
    }

    // COLLECTABLE x POKECENTER
    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        if (collectables[i].sprite.getGlobalBounds().intersects(pokecenter.sprite.getGlobalBounds())) // if Pokemon spawned on PokeCenter
        {
            std::cout << "C x PC, ";
            int newPosX, newPosY;
            newPosX = collectables[i].giveRandomNumber(0, 1920);  // select new random x position for Pokemon
            newPosY = collectables[i].giveRandomNumber(0, 900);   // select new random y position for Pokemon
            collectables[i].sprite.setPosition(newPosX, newPosY); // set new position
            field->draw(collectables[i].sprite);
            done += 1;
        }
    }

    // TREE x TREE
    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees (excluding invisible mountain rectangles)
    {
        for (int k = i + 1; k < (sizeof(trees) / sizeof(trees[0])); k++) // for all other trees (excluding invisible mountain rectangles)
        {
            if (trees[i].sprite.getGlobalBounds().intersects(trees[k].sprite.getGlobalBounds())) // if tree spawned on another tree
            {
                std::cout << "T x T, ";
                int newPosX, newPosY;
                newPosX = trainers[0].giveRandomNumber(0, 1920); // select new random x position for tree
                newPosY = trainers[0].giveRandomNumber(0, 900);  // select new random y position for tree
                trees[i].sprite.setPosition(newPosX, newPosY);   // set new position, note: keep "i" here, issue with using trees[k]: if tree spawns on invisible mountain rectangle, the rectangle will be moved instead of the tree
                field->draw(trees[i].sprite);
                done += 1;
            }
        }
    }

    // TREE x ENEMY
    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees (including invisible mountain rectangles)
    {
        for (int k = 0; k < (sizeof(trainers) / sizeof(trainers[0])); k++) // for all trainers
        {
            if (trees[i].sprite.getGlobalBounds().intersects(trainers[k].sprite.getGlobalBounds())) // if tree spawned on trainer
            {
                std::cout << "T x E, ";
                int newPosX, newPosY;
                newPosX = trainers[k].giveRandomNumber(0, 1920);  // select new random x position for trainer
                newPosY = trainers[k].giveRandomNumber(0, 900);   // select new random y position for trainer
                trainers[k].sprite.setPosition(newPosX, newPosY); // set new position
                field->draw(trainers[k].sprite);
                done += 1;
            }
        }
    }

    // TREE x POKECENTER
    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees (excluding invisible mountain rectangles)
    {
        if (trees[i].sprite.getGlobalBounds().intersects(pokecenter.sprite.getGlobalBounds())) // if tree spawned on PokeCenter
        {
            std::cout << "T x PC, ";
            int newPosX, newPosY;
            newPosX = trainers[0].giveRandomNumber(0, 1920); // select new random x position for trainer
            newPosY = trainers[0].giveRandomNumber(0, 900);  // select new random y position for trainer
            trees[i].sprite.setPosition(newPosX, newPosY);   // set new position
            field->draw(trees[i].sprite);
            done += 1;
        }
    }

    // ENEMY x ENEMY
    for (int i = 0; i < (sizeof(trainers) / sizeof(trainers[0])); i++) // for all trainers
    {
        for (int k = i + 1; k < (sizeof(trainers) / sizeof(trainers[0])); k++) // for all other trainers
        {
            if (trainers[i].sprite.getGlobalBounds().intersects(trainers[k].sprite.getGlobalBounds())) // if trainer spawns on another trainer
            {
                std::cout << "E x E, ";
                int newPosX, newPosY;
                newPosX = trainers[i].giveRandomNumber(0, 1920);  // select new random x position for trainer
                newPosY = trainers[i].giveRandomNumber(0, 900);   // select new random y position for trainer
                trainers[i].sprite.setPosition(newPosX, newPosY); // set new position
                field->draw(trainers[i].sprite);
                done += 1;
            }
        }
    }

    // ENEMY x POKECENTER
    for (int i = 0; i < (sizeof(trainers) / sizeof(trainers[0])); i++) // for all trainers
    {
        if (trainers[i].sprite.getGlobalBounds().intersects(pokecenter.sprite.getGlobalBounds())) // if trainer spawns on PokeCenter
        {
            std::cout << "E x PC, ";
            int newPosX, newPosY;
            newPosX = trainers[i].giveRandomNumber(0, 1920);  // select new random x position for trainer
            newPosY = trainers[i].giveRandomNumber(0, 900);   // select new random y position for trainer
            trainers[i].sprite.setPosition(newPosX, newPosY); // set new position
            field->draw(trainers[i].sprite);
            done += 1;
        }
    }

    if (done != 0) // if there were any spawn overlaps
    {
        std::cout << done << " overlap(s), determining new spawn layout" << std::endl;
        checkPositions(); // determine new spawn layout
    }
    else
    {
        std::cout << "Successfully loaded spawn layout" << std::endl;
    }
}

/*
    CODE FÜR NACHHER, Klassen

    void Field::checkPositions()
{
    int done = 0; // Überprüft, ob alle Entitäten an unterschiedlichen Positionen erscheinen

    // Überprüfe Überlappungen für jede Entitätstyp-Kombination
    checkOverlap(player.sprite, collectables);
    checkOverlap(player.sprite, enemies);
    checkOverlap(player.sprite, spriteTree);

    checkOverlap(collectables, collectables);
    checkOverlap(collectables, enemies);
    checkOverlap(collectables, spriteTree);
    checkOverlap(collectables, spritePC);

    checkOverlap(spriteTree, spriteTree);
    checkOverlap(spriteTree, enemies);
    checkOverlap(spriteTree, spritePC);

    checkOverlap(enemies, enemies);
    checkOverlap(enemies, spritePC);

    if (done != 0)
    {
        std::cout << done << " Überlappung(en), neue Anordnung wird bestimmt" << std::endl;
        checkPositions(); // Bestimme neue Anordnung
    }
    else
    {
        std::cout << "Erfolgreiches Laden der Anordnung" << std::endl;
    }
}

// Überprüfe Überlappung für eine Entität mit einer Gruppe von Entitäten
template <typename T>
void Field::checkOverlap(sf::Sprite &entity, T &entities)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entity.getGlobalBounds().intersects(entities[i].sprite.getGlobalBounds()))
        {
            std::cout << entityToString(entity) << " x " << entityToString(entities[i].sprite) << ", ";
            setNewPosition(entities[i].sprite);
            done++;
        }
    }
}

// Überprüfe Überlappung für zwei verschiedene Gruppen von Entitäten
template <typename T, typename U>
void Field::checkOverlap(T &group1, U &group2)
{
    for (int i = 0; i < group1.size(); i++)
    {
        for (int k = 0; k < group2.size(); k++)
        {
            if (group1[i].sprite.getGlobalBounds().intersects(group2[k].sprite.getGlobalBounds()))
            {
                std::cout << entityToString(group1[i].sprite) << " x " << entityToString(group2[k].sprite) << ", ";
                setNewPosition(group2[k].sprite);
                done++;
            }
        }
    }
}

// Setze eine neue Position für eine Entität
void Field::setNewPosition(sf::Sprite &entity)
{
    int newPosX = entity.giveRandomNumber(0, 1920);
    int newPosY = entity.giveRandomNumber(0, 900);
    entity.setPosition(newPosX, newPosY);
    field->draw(entity);
}

*****************************************************************************************************************************

void Field::checkPositions() // Note: Priority: PokeCenter/player > trees > trainers/Pokemon - lower priority changes position in case of an overlap. Consider revising to eliminate redundancies in the future.
{
    int done = 0; // Checks whether all entities spawn at distinct positions

    // Check overlaps for each entity type combination
    checkOverlap(player.sprite, collectables);
    checkOverlap(player.sprite, enemies);
    checkOverlap(player.sprite, spriteTree);

    checkOverlap(collectables, collectables);
    checkOverlap(collectables, enemies);
    checkOverlap(collectables, spriteTree);
    checkOverlap(collectables, spritePC);

    checkOverlap(spriteTree, spriteTree);
    checkOverlap(spriteTree, enemies);
    checkOverlap(spriteTree, spritePC);

    checkOverlap(enemies, enemies);
    checkOverlap(enemies, spritePC);

    if (done != 0)
    {
        std::cout << done << " overlap(s), determining new spawn layout" << std::endl;
        checkPositions(); // Determine new spawn layout
    }
    else
    {
        std::cout << "Successfully loaded spawn layout" << std::endl;
    }
}

// Check overlap for an entity with a group of entities
template <typename T>
void Field::checkOverlap(sf::Sprite &entity, T &entities)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entity.getGlobalBounds().intersects(entities[i].sprite.getGlobalBounds()))
        {
            std::cout << entityToString(entity) << " x " << entityToString(entities[i].sprite) << ", ";
            setNewPosition(entities[i].sprite);
            done++;
        }
    }
}

// Check overlap for two different groups of entities
template <typename T, typename U>
void Field::checkOverlap(T &group1, U &group2)
{
    for (int i = 0; i < group1.size(); i++)
    {
        for (int k = 0; k < group2.size(); k++)
        {
            if (group1[i].sprite.getGlobalBounds().intersects(group2[k].sprite.getGlobalBounds()))
            {
                std::cout << entityToString(group1[i].sprite) << " x " << entityToString(group2[k].sprite) << ", ";
                setNewPosition(group2[k].sprite);
                done++;
            }
        }
    }
}

// Set a new position for an entity
void Field::setNewPosition(sf::Sprite &entity)
{
    int newPosX = entity.giveRandomNumber(0, 1920);
    int newPosY = entity.giveRandomNumber(0, 900);
    entity.setPosition(newPosX, newPosY);
    field->draw(entity);
}


*/
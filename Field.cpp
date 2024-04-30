#include "Field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono> //include all necessary external files

Field::Field() : Subject() // constructor
{
    std::cout << "Field constructor" << std::endl;

    // SET VISUALS - FIELD
    // field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen); // open a full-screen window called "Pokemon-Hunt"
    window_field = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Pokemon-Hunt"); // open a 1920x1080 window called "Pokemon-Hunt", IMPORTANT: only use this if upper method doesn't work properly on your device (for example if secondary monitor is used)
    window_field->setFramerateLimit(60);                                            // don't exceed a framerate of 60fps
    texturef.loadFromFile("resources/backgroundv3.png");                            // load background image
    texturef.setSmooth(true);
    spritef.setTexture(texturef);                                                                    // set field sprite to background image
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2, texturef.getSize().y / 2));             // move origin of sprite (default: top left) to center of sprite
    spritef.setPosition(sf::Vector2f(window_field->getSize().x / 2, window_field->getSize().y / 2)); // place background sprite in the middle of the screen
    dimOverlay.setSize(sf::Vector2f(window_field->getSize().x, window_field->getSize().y));          // create a rectangle with the size of the screen
    dimOverlay.setFillColor(sf::Color(0, 0, 0, 150));                                                // set color of rectangle to transparent

    // SET VISUALS - OBSTACLES
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

    checkPositions(); // check whether entities tried to spawn on one another when they weren't supposed to

    menuIsOpen = false; // menu is not open at the beginning of the game
    prevMenuKeyPressed = false;
    moves = 0;    // initialize the moves variable which is used for the score calculation
    gamemode = 0; // set gamemode to normal mode
}

Field::~Field() // destructor
{
    std::cout << "Field destructor" << std::endl;
    delete window_field; // delete the field
}

const bool Field::getFieldIsOpen() const // returns whether field is open
{
    return window_field->isOpen();
}

void Field::changeGamemode(int pGamemode)
{
    if (pGamemode == 1) // if gamemode is survival
    {
        gamemode = 1;
        realTimeClock.restart();

        player.spawnPX = window_field->getSize().x / 2; // set spawn and position of player to center of screen
        player.spawnPY = window_field->getSize().y / 2;
        playerPosX = window_field->getSize().x / 2;
        playerPosY = window_field->getSize().y / 2;
        player.sprite.setPosition(playerPosX, playerPosY);

        notify(3, player.getSpeed(), player.getCollected()); // set 3 health points to player
        resetGame();                                         // reset game

        pokemonhollow.loadFromFile("resources/pokemon_hollow.ttf");                                                                                                                        // load pokemon font
        timescore.setFont(pokemonhollow);                                                                                                                                                  // use loaded font
        timescore.setString("Time: " + std::to_string(static_cast<int>(elapsedTime)) + "." + std::to_string(static_cast<int>((elapsedTime - static_cast<int>(elapsedTime)) * 10)) + " s"); // print score on screen
        timescore.setCharacterSize(65);                                                                                                                                                    // set size of score
        timescore.setFillColor(sf::Color::White);                                                                                                                                          // set color of score
        timescore.setPosition(sf::Vector2f(100, 960));                                                                                                                                     // set position of score
    }
    else
    {
        player.spawnPX = 550; // set spawn position to top left of screen
        player.spawnPY = 200;
        gamemode = 0;
        resetGame();
    }
}

void Field::handleSliderMovement(sf::RectangleShape &pSliderHandle, sf::Event &pEvent)
{
    static bool isSliderPressed = false; // check if slider is pressed
    static sf::Vector2f lastMousePos;    // lase mouse position when pressind the slider

    sf::Vector2i mousePos = sf::Mouse::getPosition();
    sf::FloatRect handleBounds = pSliderHandle.getGlobalBounds();
    handleBounds.top += 25; // move the global bounds of the handle 25 pixels down, so it fits the visual representation of the slider

    if (handleBounds.contains(static_cast<sf::Vector2f>(mousePos)) || isSliderPressed)
    {
        pSliderHandle.setOutlineColor(sf::Color::Black); // set black outline if mouse is over the slider
    }
    else
    {
        pSliderHandle.setOutlineColor(sf::Color::Transparent); // no outline if mouse is not over the slider
    }

    if (pEvent.type == sf::Event::MouseButtonPressed && pEvent.mouseButton.button == sf::Mouse::Left)
    {
        if (handleBounds.contains(static_cast<sf::Vector2f>(mousePos)))
        {
            pSliderHandle.setOutlineColor(sf::Color::Black); // black outline if slider handle is pressed
            isSliderPressed = true;
            lastMousePos = static_cast<sf::Vector2f>(mousePos);
        }
    }
    else if (pEvent.type == sf::Event::MouseButtonReleased && pEvent.mouseButton.button == sf::Mouse::Left)
    {
        pSliderHandle.setOutlineColor(sf::Color::Transparent); // no outline if mouse is not pressing the slider
        isSliderPressed = false;
    }
    else if (pEvent.type == sf::Event::MouseMoved && isSliderPressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        float deltaX = static_cast<float>(mousePos.x) - lastMousePos.x; // change handle position
        float newX = pSliderHandle.getPosition().x + deltaX;

        float leftLimit = 1400.f; // set boundaries for the slider handle
        float rightLimit = 1775.f;
        if (newX < leftLimit)
        {
            newX = leftLimit;
        }
        else if (newX > rightLimit)
        {
            newX = rightLimit;
        }

        pSliderHandle.setPosition(newX, pSliderHandle.getPosition().y); // set new position of slider handle
    }
}

void Field::handleButtonEvents(sf::RectangleShape &pButton, sf::Event &pEvent)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(); // mouse position on screen

    sf::Vector2f mousePosRelativeToWindow = window_field->mapPixelToCoords(mousePos); // mouse position relative to window

    sf::FloatRect buttonBounds = pButton.getGlobalBounds();
    buttonBounds.top += 25.f; // correct the position of the button bounds to match the visual representation

    if (buttonBounds.contains(mousePosRelativeToWindow))
    {
        pButton.setOutlineColor(sf::Color::Red); // set outline red if mouse is over the button
    }
    else
    {
        pButton.setOutlineColor(sf::Color(248, 208, 80, 255)); // set yellow outline if mouse is not over the button
    }

    if (pEvent.type == sf::Event::MouseButtonPressed && pEvent.mouseButton.button == sf::Mouse::Left)
    {
        if (buttonBounds.contains(mousePosRelativeToWindow))
        {
            pButton.setOutlineColor(sf::Color::Black); // black outline when mouse presses button
        }
    }
    else if (pEvent.type == sf::Event::MouseButtonReleased && pEvent.mouseButton.button == sf::Mouse::Left)
    {
        if (buttonBounds.contains(mousePosRelativeToWindow))
        {
            pButton.setOutlineColor(sf::Color::Red);

            if (&pButton == &menu.button_mode2) // was the survival mode button pressed?
            {
                if (menuIsOpen == true)
                {
                    changeGamemode(1); // change gamemode to survival
                }
            }
            else if (&pButton == &menu.button_mode1)
            {
                if (menuIsOpen == true)
                {
                    changeGamemode(0); // if normal was pressed, change to normal
                }
            }
        }
        else
        {
            pButton.setOutlineColor(sf::Color(248, 208, 80, 255)); // red outline if mouse is not hovering over button
        }
    }
}

void Field::drawMenu()
{
    window_field->draw(dimOverlay);
    window_field->draw(menu.sprite);
    window_field->draw(menu.text_difficulty);
    window_field->draw(menu.text_mode);
    window_field->draw(menu.text_volume);
    window_field->draw(menu.button_mode1.getText());
    window_field->draw(menu.button_mode2.getText());
    window_field->draw(menu.button_difficulty1.getText());
    window_field->draw(menu.button_difficulty2.getText());
    window_field->draw(menu.button_difficulty3.getText());
    window_field->draw(menu.button_mode1);
    window_field->draw(menu.button_mode2);
    window_field->draw(menu.button_difficulty1);
    window_field->draw(menu.button_difficulty2);
    window_field->draw(menu.button_difficulty3);
    window_field->draw(menu.slider_volume);
    window_field->draw(menu.sliderhandle_volume);
}

void Field::checkCollision()
{
    if (gamemode != 1) // only check trainers and collectables if gamemode is normal
    {
        for (int i = 0; i < (sizeof(trainers) / sizeof(trainers[0])); i++) // for all trainers
        {
            if (player.sprite.getGlobalBounds().intersects(trainers[i].sprite.getGlobalBounds())) // if player touches trainer
            {
                std::cout << "Player hit trainer" << std::endl;
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
                notify(player.getHealthPoints(), player.getSpeed(), player.getCollected() + 1); // increase amount of collected Pokemon by 1
                std::cout << "Player has collected " << player.getCollected() << " Pokemon" << std::endl;
                collectables[i].sprite.setScale(0.5, 0.5); // shrink collected Pokemon
                sounds.collected.play();                   // play sound effect for collecting Pokemon

                if ((sizeof(collectables) / sizeof(collectables[0])) > 1) // if there are 2 or more Pokemon to collect
                {
                    collectables[i].sprite.setPosition(115 + (271 / ((sizeof(collectables) / sizeof(collectables[0])) - 1) * (player.getCollected() - 1)), 1020); // move collected Pokemon to the CPB. The rather complex calculation makes any amount of collectables possible.
                    // 115  = spriteCPB.getPosition().x - textureCPB.getSize().x / 2 + 25                                                                     //explains the origin of the "115"  above in case a different sized CPB is needed
                    // 271 = spriteCPB.getPosition().x + textureCPB.getSize().x / 2 - 25 - collectables[i].getTexture().x - (92)                             //explains the origin of the "271" above in case a different sized CPB is needed
                }
                else // if there's only 1 Pokemon
                {
                    collectables[i].sprite.setPosition(pokebox.sprite.getPosition().x - collectables[i].sprite.getTexture()->getSize().x / 2, 1000); // place it in the center of the CPB
                }
            }
        }
    }

    for (int i = 0; i < (sizeof(pokeballs) / sizeof(pokeballs[0])); i++) // for all Pokeballs
    {
        if (player.sprite.getGlobalBounds().intersects(pokeballs[i].sprite.getGlobalBounds())) // if player touches Pokeball
        {
            updateHealth(); // update health
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
            sounds.win.play(); // play sound effect for winning the game

            score = (1150 - moves) / (4 - player.getHealthPoints()); // calculate score based on moves made & HP left
            // note: you need around 150 moves minimum to get from spawn to PokeCenter, thus, the highest possible score is ~1000
            if (score < 100) // if player scores less than 100 points
            {
                score = 100; // award him with 100 points anyways to keep a feeling of success (:
            }
            std::cout << "Score: " << score << std::endl;

            pokemonhollow.loadFromFile("resources/pokemon_hollow.ttf");              // load pokemon font
            textscore.setFont(pokemonhollow);                                        // use loaded font
            textscore.setString("Score: " + std::to_string(score));                  // print score on screen
            textscore.setCharacterSize(96);                                          // set size of score
            textscore.setFillColor(sf::Color::Black);                                // set color of score
            textscore.setPosition(sf::Vector2f(100, window_field->getSize().y / 4)); // set position of score

            success = 1;                  // player did win
            endOfGame(success, gamemode); // show success screen
        }
    }
}

void Field::updateHealth()
{
    if ((gamemode == 1 && healthUpdateTimer.getElapsedTime() >= SpawnProof)) // if player is in survival mode and spawn proof is over
    {
        player.sprite.setPosition(window_field->getSize().x / 2, window_field->getSize().y / 2); // reset player sprite position
        player.shapeP.setPosition(window_field->getSize().x / 2, window_field->getSize().y / 2); // reset player shape  position
    }

    if (healthUpdateTimer.getElapsedTime() >= SpawnProof || gamemode == 0) // if spawn proof is over or player is in normal mode
    {
        std::cout << "Player hit Pokeball" << std::endl;

        player.sprite.setPosition(sf::Vector2f(player.spawnPX, player.spawnPY)); // reset player sprite position
        player.shapeP.setPosition(sf::Vector2f(player.spawnPX, player.spawnPY)); // reset player shape  position
        notify(player.getHealthPoints() - 1, player.getSpeed(), player.getCollected());
        healthUpdateTimer.restart();
        sounds.damage.play(); // play sound effect for getting damaged
        std::cout << "Player has " << player.getHealthPoints() << " HP left" << std::endl;
        // damage animation with red shape
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
            window_field->draw(player.shapeP); // draw player shape
            window_field->display();           // display updated frame
            Sleep(100);                        // wait 0.1s
        }

        healthbar.setTexture("resources/health_bar_" + std::to_string(player.getHealthPoints()) + ".png"); // load health bar with remaining HP

        if (player.getHealthPoints() == 0) // if remaining HP = 0
        {
            std::cout << "Player lost" << std::endl;
            sounds.failure.play();        // play sound effect for losing the game
            success = 0;                  // player didn't win
            endOfGame(success, gamemode); // show death screen
        }
    }
}

void Field::openMenu()
{
    dimOverlay.setFillColor(sf::Color(0, 0, 0, 150));
    window_field->draw(dimOverlay); // draw rectangle
    menu.sprite.setPosition(960, 540);
    menuIsOpen = true;
    drawMenu(); // draw menu
}

void Field::closeMenu()
{
    menu.sprite.setPosition(sf::Vector2f(-1000, -1000)); // set position out of view to "destroy" it
    window_field->draw(menu.sprite);                     // draw menu
    dimOverlay.setFillColor(sf::Color::Transparent);     // set color of rectangle to transparent
    window_field->draw(dimOverlay);                      // draw rectangle
    menuIsOpen = false;
}

void Field::endOfGame(int pSuccess, int pGamemode)
{
    window_field->clear(); // clear last frame

    if (pSuccess == 0 && pGamemode == 0) // if player lost
    {
        endOfGameSprite.setTexture("resources/death_sprite.png");
        endOfGameMessage.setTexture("resources/death_message.png");
        endOfGameMessage.initializeSpriteAndTexture();
        endOfGameSprite.initializeSpriteAndTexture();
    }
    else // otherwise
    {
        endOfGameSprite.setTexture("resources/success_sprite.png");
        endOfGameMessage.setTexture("resources/success_message.png");
        endOfGameMessage.initializeSpriteAndTexture();
        endOfGameSprite.initializeSpriteAndTexture();
    }

    endOfGameSprite.sprite.setPosition(sf::Vector2f(window_field->getSize().x / 2, window_field->getSize().y / 3));      // set position for success/death sprite
    endOfGameMessage.sprite.setPosition(sf::Vector2f(window_field->getSize().x / 2, window_field->getSize().y / 4 * 3)); // set position for success/death message

    // DRAW ALL ENTITIES OF ENDOFGAME SCREEN
    window_field->draw(spritef);

    if (pGamemode == 0)
    {
        window_field->draw(pokecenter.sprite);
    }

    for (int i = 0; i < (sizeof(trees) / sizeof(trees[0])); i++) // for all trees (excluding invisible mountain rectangles)
    {
        window_field->draw(trees[i].sprite);
    }
    window_field->draw(mountainTopLeft.sprite);
    window_field->draw(mountainTopRight.sprite);
    window_field->draw(healthbar.sprite);

    if (pSuccess == 1 && pGamemode == 0)
    {
        window_field->draw(textscore);
    }
    else if (pSuccess == 0 && pGamemode == 1)
    {
        timescore.setCharacterSize(96);
        timescore.setFillColor(sf::Color::Black);
        timescore.setPosition(sf::Vector2f(100, window_field->getSize().y / 4));
        window_field->draw(timescore);
    } // only draw score if player won

    window_field->draw(endOfGameSprite.sprite);
    window_field->draw(endOfGameMessage.sprite);

    window_field->display(); // display updated frame

    while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
    } // wait until player resets or quits

    resetGame(); // reset the game
}

void Field::resetGame()
{
    elapsedTime = 0;
    realTimeClock.restart();
    timescore.setString("Time: 0.0 s");
    notify(3, player.getSpeed(), 0);
    moves = 0;                                          // reset move counter
    healthbar.setTexture("resources/health_bar_3.png"); // load health bar with 3 HP
    window_field->draw(healthbar.sprite);
    playerPosX = player.spawnPX; // reset player position (X)
    playerPosY = player.spawnPY; // reset player position (Y)
    window_field->draw(player.sprite);
    for (int i = 0; i < (sizeof(collectables) / sizeof(collectables[0])); i++) // for all Pokemon
    {
        if (collectables[i].sprite.getGlobalBounds().intersects(pokebox.sprite.getGlobalBounds())) // if Pokemon was collected before / is placed on the CPB
        {
            collectables[i].sprite.setScale(1, 1); // enlarge Pokemon to original size
        }
        collectables[i].sprite.setPosition(positionCX[i], positionCY[i]); // place Pokemon at original spawn position
    }

    for (int i = 0; i < (sizeof(pokeballs) / sizeof(pokeballs[0])); i++) // for all Pokeballs
    {
        pokeballs[i].speed = pokeballs[i].giveRandomDouble(7.5, 9.5);
        int newPosY;
        newPosY = pokeballs[i].giveRandomNumber(0, 900); // select new random spawn height
        pokeballs[i].sprite.setPosition(1970, newPosY);  // set Pokeball position to the right of the screen at selected height
        window_field->draw(pokeballs[i].sprite);
    }
}

template <typename T, typename U>
void Field::checkOverlap(T &pGroup1, U &pGroup2, int pSize1, int pSize2, int &pDone)
{
    for (int i = 0; i < pSize1; ++i) // check collision between two objects saved in an array
    {
        for (int j = 0; j < pSize2; ++j)
        {
            if (i != j || typeid(T) != typeid(U))
            {
                if (pGroup1[i].sprite.getGlobalBounds().intersects(pGroup2[j].sprite.getGlobalBounds()))
                {
                    setNewPosition(pGroup1[i].sprite); // move object to new position if collision was detected
                    pDone++;
                }
            }
        }
    }
}

template <typename U>
void Field::checkOverlapP(Player &player, U &pGroup1, int pSize1, int &pDone) // overload for player and object
{
    for (int i = 0; i < pSize1; ++i)
    {
        if (pGroup1[i].sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
        {
            setNewPosition(pGroup1[i].sprite);
            pDone++;
        }
    }
}

template <typename T>
void Field::checkOverlapPC(PokeCenter &pokeCenter, T &pGroup1, int pSize1, int &pDone)
{
    for (int i = 0; i < pSize1; ++i)
    {
        if (pGroup1[i].sprite.getGlobalBounds().intersects(pokeCenter.sprite.getGlobalBounds()))
        {
            setNewPosition(pGroup1[i].sprite);
            pDone++;
        }
    }
}

void Field::setNewPosition(sf::Sprite &pEntity)
{
    int newPosX, newPosY;
    newPosX = trainers[0].giveRandomNumber(0, 1920); // select new random x position for entity
    newPosY = trainers[0].giveRandomNumber(0, 900);  // select new random y position for entity
    pEntity.setPosition(newPosX, newPosY);           // set new position
    window_field->draw(pEntity);
}

void Field::checkPositions()
{
    int done = 0; // checks if no collisions were detected

    checkOverlapP(player, collectables, sizeof(collectables) / sizeof(collectables[0]), done); // Player x Pokémon

    checkOverlapP(player, trainers, sizeof(trainers) / sizeof(trainers[0]), done); // Player x Trainer

    checkOverlapP(player, trees, sizeof(trees) / sizeof(trees[0]), done); // Player x Tree

    checkOverlap(collectables, collectables, sizeof(collectables) / sizeof(collectables[0]), sizeof(collectables) / sizeof(collectables[0]), done); // Pokémon x Pokémon

    checkOverlap(collectables, trainers, sizeof(collectables) / sizeof(collectables[0]), sizeof(trainers) / sizeof(trainers[0]), done); // Pokémon x Trainer

    checkOverlap(collectables, trees, sizeof(collectables) / sizeof(collectables[0]), sizeof(trees) / sizeof(trees[0]), done); // Pokémon x Tree

    checkOverlapPC(pokecenter, collectables, sizeof(collectables) / sizeof(collectables[0]), done); // Pokémon x PokeCenter

    checkOverlap(trainers, trainers, sizeof(trainers) / sizeof(trainers[0]), sizeof(trainers) / sizeof(trainers[0]), done); // Trainer x Trainer

    checkOverlap(trainers, trees, sizeof(trainers) / sizeof(trainers[0]), sizeof(trees) / sizeof(trees[0]), done); // Trainer x Tree

    checkOverlapPC(pokecenter, trainers, sizeof(trainers) / sizeof(trainers[0]), done); // Trainer x PokeCenter

    checkOverlap(trees, trees, sizeof(trees) / sizeof(trees[0]), sizeof(trees) / sizeof(trees[0]), done); // Tree x Tree

    checkOverlapPC(pokecenter, trees, sizeof(trees) / sizeof(trees[0]), done); // Tree x PokeCenter

    if (done != 0) // repeat if collisions were detected
    {
        std::cout << done << " collision(s), new layout is generated" << std::endl;
        checkPositions();
    }
    else
    {
        std::cout << "layout successfully loaded" << std::endl;
    }
}

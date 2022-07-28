#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono>           //include all necessary external files

Field::Field()
{
    std::cout << "Field constructor" << std::endl;
    
    //SET VISUALS - FIELD
    //field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen);   //open a full-screen window called "Pokemon-Hunt"
    field = new sf::RenderWindow(sf::VideoMode(1920,1080), "Pokemon-Hunt");                                 //open a 1920x1080 window called "Pokemon-Hunt", IMPORTANT: only use this if upper method doesn't work properly on your device (for example if secondary monitor is used)
    field->setFramerateLimit(60);   	                        //don't exceed a framerate of 60fps
    texturef.loadFromFile("resources/backgroundv3.png");        //load background image
    texturef.setSmooth(true);
    spritef.setTexture(texturef);                               //set field sprite to background image
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2, texturef.getSize().y / 2));    //move origin of sprite (default: top left) to center of sprite 
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));      //place background sprite in the middle of the screen
    
    //SET VARIABLES - SOUND
    bufferC.loadFromFile("resources/collected.wav");            //load sound effects
    bufferW.loadFromFile("resources/win.wav");
    bufferF.loadFromFile("resources/failure.wav");
    bufferD.loadFromFile("resources/damage.wav");
    collected.setBuffer(bufferC);                               //set buffer for each sound effect
    win.setBuffer(bufferW);
    failure.setBuffer(bufferF);
    damage.setBuffer(bufferD);
    collected.setVolume(70);                                    //set volume for each sound effect
    win.setVolume(55);
    failure.setVolume(25);
    damage.setVolume(35);
    
    //SET VISUALS - HEALTH-BAR
    textureHB.loadFromFile("resources/health_bar_3.png");       //load full health bar
    textureHB.setSmooth(true);
    spriteHB.setTexture(textureHB);                             //set health bar sprite to full health bar image
    spriteHB.setOrigin(sf::Vector2f(textureHB.getSize().x / 2,textureHB.getSize().y / 2));      //move origin of sprite (default: top left) to center of sprite 
    spriteHB.setPosition(1600,50);                              //place health bar sprite in the top right of the screen
    
    //SET VISUALS - COLLECTED POKEMON BOX
    textureCPB.loadFromFile("resources/collected_pokemon.png"); //load collected Pokemon box
    textureCPB.setSmooth(true);
    spriteCPB.setTexture(textureCPB);                           //set collected Pokemon sprite to collected Pokemon box
    spriteCPB.setOrigin(sf::Vector2f(textureCPB.getSize().x / 2, textureCPB.getSize().y / 2));  //move origin of sprite (default: top left) to center of sprite 
    spriteCPB.setPosition(250,1000);                            //place collected Pokemon sprite in the bottom left of the screen
    
    //SET VISUALS - POKE CENTER
    texturePC.loadFromFile("resources/pokecenter.png");         //load Pokecenter image
    texturePC.setSmooth(true);
    spritePC.setTexture(texturePC);                             //set Pokecenter sprite to Pokecenter image
    spritePC.setOrigin(sf::Vector2f(texturePC.getSize().x / 2,texturePC.getSize().y / 2));      //move origin of sprite (default: top left) to center of sprite
    spritePC.setPosition(1800,500);                             //place Pokecenter sprite on the right of the screen
    
    //SET VISUALS - TREES
    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)     //for all trees and invisible rectangles. Note: lack of giveRandomNumber function: using giveRandomNumber of enemies[0]
    {
        if(i < amountOfTrees) 
        {
            textureTree[i].loadFromFile("resources/tree_" + std::to_string(enemies[0].giveRandomNumber(1,1)) + ".png");  //load random tree image
            textureTree[i].setSmooth(true);
            spriteTree[i].setTexture(textureTree[i]);                       //set current tree sprite to selected tree image
            spriteTree[i].setOrigin(sf::Vector2f(textureTree[i].getSize().x / 2, textureTree[i].getSize().y / 2));  //move origin of sprite (default: top left) to center of sprite
            spriteTree[i].setPosition(enemies[0].giveRandomNumber(0,1920), enemies[0].giveRandomNumber(0,900));     //set tree sprite at random spot on the map
        } else if(i == (amountOfTrees-1) + 1) 
        {
            textureTree[i].loadFromFile("resources/mountainTopRight.png");  //load transparent image in size of the invisible rectangle needed
            textureTree[i].setSmooth(true);
            spriteTree[i].setTexture(textureTree[i]);                       //set current "tree" sprite to transparent image. This was done due to the fact that these rectangles act in the same way as trees do.
            spriteTree[i].setPosition(texturef.getSize().x - textureTree[i].getSize().x, -3);    //set "tree" sprite in the top right of the screen
        } else if(i == (amountOfTrees-1) + 2) 
        {
            textureTree[i].loadFromFile("resources/mountainTopLeft.png");   //load transparent image in size of the invisible rectangle needed
            textureTree[i].setSmooth(true);
            spriteTree[i].setTexture(textureTree[i]);                       //set current "tree" sprite to transparent image. This was done due to the fact that these rectangles act in the same way as trees do.
            spriteTree[i].setPosition(0, 0);                                //set "tree" sprite in the top left of the screen
        }
    }  
        
    moves = 0;          //initialize the moves variable which is used for the score calculation
    checkPositions();   //check whether entities tried to spawn on one another when they weren't supposed to
}

Field::~Field()         //destructor
{
    std::cout << "Field destructor" << std::endl;
    delete field;       //delete the field
}

const bool Field::getFieldIsOpen() const            //returns whether field is open
{
    return field->isOpen();                             
}

void Field::update()                                //manages all the game data
{
    playerPosX = player.spriteP.getPosition().x;    //save current player x position
    playerPosY = player.spriteP.getPosition().y;    //save current player y position

    int movement, speed;
    movement = playerPosY + playerPosX;             //walking animation, as long as speed is odd
    speed = player.getSpeed();                      //receives player speed as initialized in player.cpp

    sf::Event event;
    
    while(field->pollEvent(event));                         //as long as any input is being made
    { 
        if(event.type == sf::Event::Closed)             //if window gets closed by user
        {
            field->close();                             //close everything
        }
        if(InputDelayTimer.getElapsedTime() > InputDelay)   //if a certain input delay has passed
        {
            if((InputDelayTimer.getElapsedTime() > InputDelay) && ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::R)))))
            {                                               //and if any of the 6 used keys is pressed
                //CLOSE/RESET
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))   //if "Esc" is pressed
                {
                    field->close();                                     //close everything
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))        //if "R" is pressed
                {
                    resetGame();                                        //reset the game
                }

                //WASD MOVEMENT
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))         //if "W" is pressed
                {
                    direction = 0;                                      //current direction: up
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png");        //alternate between the two animation frames
                    playerPosY -= speed;                                //move player up
                    moves++;                                            //player has done a move
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))    //if "W" is pressed
                {
                    direction = 1;                                      //current direction: left
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png");    //alternate between the two animation frames
                    playerPosX -= speed;                                //move player to the right
                    moves++;                                            //player has done a move
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))    //if "S" is pressed
                {
                    direction = 2;                                      //current direction: down
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png");    //alternate between the two animation frames
                    playerPosY += speed;                                //move player down
                    moves++;                                            //player has done a move
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))    //if "D" is pressed
                {
                    direction = 3;                                      //current direction: right
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 6) + ".png");    //alternate between the two animation frames
                    playerPosX += speed;                                //move player right
                    moves++;                                            //player has done a move
                }

                InputDelayTimer.restart();                              //restart input delay timer

            }
        }
                
        //Window borders - keeping the player half its size away from any edges of the field
        if(playerPosX < (player.spriteP.getTexture()->getSize().x) / 2)
        {
            playerPosX = (player.spriteP.getTexture()->getSize().x) / 2;
        }
        if(playerPosX > (int)field->getSize().x - (player.spriteP.getTexture()->getSize().x) / 2)
        {
            playerPosX = field->getSize().x - (player.spriteP.getTexture()->getSize().x) / 2;
        }
        if(playerPosY < (player.spriteP.getTexture()->getSize().y) / 2)
        {
            playerPosY = (player.spriteP.getTexture()->getSize().y) / 2;
        }
        if(playerPosY > 920 - (player.spriteP.getTexture()->getSize().y) / 2)   //920 in order to prevent player from walking across the trees of the background image
        {
            playerPosY = 920 - (player.spriteP.getTexture()->getSize().y) / 2;  //920 in order to prevent player from walking across the trees of the background image
        }

        player.spriteP.setPosition(playerPosX, playerPosY);     //set player sprite to updated position
        player.shapeP.setPosition(playerPosX, playerPosY);      //set player shape  to updated position
    }
}

void Field::render()                    //displays the game field
{
    field->clear();                     //clear last frame

    //DRAW ALL ENTITIES
    field->draw(spritef);
    field->draw(spriteHB);
    field->draw(spriteCPB);
    field->draw(spritePC);
    
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)               //for all trainers
    {
        field->draw(enemies[i].spriteE);
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)     //for all Pokemon
    {
        field->draw(collectables[i].spriteC);
        
        if(!(collectables[i].spriteC.getGlobalBounds().intersects(spriteCPB.getGlobalBounds())))        //if collectable is not intersecting with the collected Pokemon box
        {
            positionCX[i] = collectables[i].spriteC.getPosition().x;                                    //save its X position in a variable (used for resetting game)
            positionCY[i] = collectables[i].spriteC.getPosition().y;                                    //save its Y position in a variable (used for resetting game)
        }

    }

    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++)           //for all Pokeballs
    {
        field->draw(pokeballs[i].spriteE2);
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)         //for all trees
    {
        field->draw(spriteTree[i]);
    }

    pokeballMovement();             //moving Pokeballs
    checkCollision();               //checking for any sort of player - entity collision

    field->draw(player.spriteP);

    field->display();               //display updated frame
}

void Field::pokeballMovement()
{
    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++) {     //for all Pokeballs
        pokeballs[i].spriteE2.setPosition(((pokeballs[i].spriteE2.getPosition().x) - pokeballs[i].speed), pokeballs[i].spriteE2.getPosition().y);   //move Pokeball to the left (by an amount depending on its speed)
        
        if(pokeballs[i].spriteE2.getPosition().x <= -100)                   //if Pokeball has passed the left screen border
        {
            pokeballs[i].speed = pokeballs[i].fRand(7.5,9.5);               //select new random speed
            int newPosY;
            newPosY = pokeballs[i].giveRandomNumber(0,900);                 //select new random spawn height
            pokeballs[i].spriteE2.setPosition(1970, newPosY);               //set Pokeball position to the right of the screen at selected height
        }
    }
}

void Field::checkCollision()
{
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)                                   //for all trainers
    {
        if(player.spriteP.getGlobalBounds().intersects(enemies[i].spriteE.getGlobalBounds()))       //if player touches trainer
        {
            std::cout << "Player hit trainer" << std::endl;
            player.setHealthPoints(player.getHealthPoints() - 1);                                   //reduce HP by 1
            std::cout << "Player has " << player.getHealthPoints() << " HP left" << std::endl;
            player.spriteP.setPosition(sf::Vector2f(player.spawnPX,player.spawnPY));                //reset player sprite position
            player.shapeP.setPosition(sf::Vector2f(player.spawnPX,player.spawnPY));                 //reset player shape  position
            updateHealth();                                                                         //update health
        }
    }

    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++)                               //for all Pokeballs
    {
        if(player.spriteP.getGlobalBounds().intersects(pokeballs[i].spriteE2.getGlobalBounds()))    //if player touches Pokeball
        {
            std::cout << "Player hit Pokeball" << std::endl;
            player.setHealthPoints(player.getHealthPoints() -1);                                    //reduce HP by 1
            std::cout << "Player has " << player.getHealthPoints() << " HP left" << std::endl;
            player.spriteP.setPosition(sf::Vector2f(player.spawnPX,player.spawnPY));                //reset player sprite position
            player.shapeP.setPosition(sf::Vector2f(player.spawnPX,player.spawnPY));                 //reset player shape  position
            updateHealth();                                                                         //update health
        }
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)                         //for all Pokemon
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].spriteC.getGlobalBounds()))  //if player touches Pokemon
        {
            std::cout << "Player collected Pokemon" << std::endl;
            player.setCollected(player.getCollected() + 1);                                         //increase amount of collected Pokemon by 1
            std::cout << "Player has collected " << player.getCollected() << " Pokemon" << std::endl;
            collectables[i].spriteC.setScale(0.5, 0.5);                                             //shrink collected Pokemon
            collected.play();                                                                       //play sound effect for collecting Pokemon

            if((sizeof(collectables)/sizeof(collectables[0])) > 1)      //if there are 2 or more Pokemon
            {
                collectables[i].spriteC.setPosition(92 + (271/((sizeof(collectables)/sizeof(collectables[0]))-1) * (player.getCollected()-1)), 1000);   //move collected Pokemon to the CPB. The rather complex calculation makes any amount of collectables possible.
                //92  = spriteCPB.getPosition().x - textureCPB.getSize().x / 2 + 25                                                                     //explains the origin of the "92"  above in case a different sized CPB is needed
                //271 = spriteCPB.getPosition().x + textureCPB.getSize().x / 2 - 25 - collectables[i].getTexture().x - (92)                             //explains the origin of the "271" above in case a different sized CPB is needed
            } else                                                      //if there's only 1 Pokemon
            {
                collectables[i].spriteC.setPosition(spriteCPB.getPosition().x - collectables[i].spriteC.getTexture()->getSize().x / 2, 1000);           //place it in the center of the CPB
            }
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)                             //for all trees
    {
        while(player.spriteP.getGlobalBounds().intersects(spriteTree[i].getGlobalBounds()))         //as long as player is within the tree
        {
            switch(direction){      //note: moving the player one pixel at a time here to prevent the feeling of false hitboxes
                case 0:             //if direction is up
                playerPosY++;       //move player down
                break;
                case 1:             //if direction is left
                playerPosX++;       //move player to the right
                break;
                case 2:             //if direction is down
                playerPosY--;       //move player up
                break;
                case 3:             //if direction is right
                playerPosX--;       //move player to the left
                break;
            }
            player.spriteP.setPosition(playerPosX, playerPosY);     //set new player position
        }
    }

    if(player.spriteP.getGlobalBounds().intersects(spritePC.getGlobalBounds()))                     //if player touches PokeCenter
    {
        if (player.getCollected() >= sizeof(collectables)/sizeof(collectables[0]))                  //if player has collected all Pokemon
        {
            std::cout << "Player wins" << std::endl;
            win.play();                                                                             //play sound effect for winning the game

            score = (1150 - moves) / (4 - player.getHealthPoints());            //calculate score based on moves made & HP left
            //note: you need around 150 moves minimum to get from spawn to PokeCenter, thus, the highest possible score is ~1000
            if(score < 100)     //if player scores less than 100 points
            {
                score = 100;    //award him with 100 points anyways to keep a feeling of success (:
            }
            std::cout << "Score: " << score << std::endl;

            pokemonhollow.loadFromFile("resources/pokemon_hollow.ttf");         //load pokemon font
            textscore.setFont(pokemonhollow);                                   //use loaded font
            textscore.setString("Score: " + std::to_string(score));             //print score on screen
            textscore.setCharacterSize(96);                                     //set size of score
            textscore.setFillColor(sf::Color::Black);                           //set colour of score
            textscore.setPosition(sf::Vector2f(100, field->getSize().y / 4));   //set position of score

            success = 1;                                                        //player did win
            endOfGame(success);                                                 //show success screen
        }
    }

}

void Field::updateHealth()
{
    damage.play();  //play sound effect for getting damaged
    for (int i = 0; i < 3; i++)                                 //for 3 iterations
    {
        if(i % 2 == 0)                                          //alternate between...
        {
            player.shapeP.setFillColor(sf::Color::Red);         //player turns red

        } else if(i % 2 != 0)                                   //...and...
        {
            player.shapeP.setFillColor(sf::Color::Transparent); //player turns invisible
        }
        field->draw(player.shapeP);                             //draw player shape
        field->display();                                       //display updated frame
        Sleep(100);                                             //wait 0.1s
    }

    if(player.getHealthPoints()== 2)                            //if remaining HP = 2
    {
        textureHB.loadFromFile("resources/health_bar_2.png");   //load health bar with 2 HP
        spriteHB.setTexture(textureHB);                         //set health bar sprite to 2 HP HB image
    } else if(player.getHealthPoints() == 1)                    //if remaining HP = 1
    {
        textureHB.loadFromFile("resources/health_bar_1.png");   //load health bar with 1 HP
        spriteHB.setTexture(textureHB);                         //set health bar sprite to 1 HP HB image
    } else if(player.getHealthPoints() == 0)                    //if remaining HP = 0
    {
        textureHB.loadFromFile("resources/health_bar_0.png");   //load health bar with 0 HP
        spriteHB.setTexture(textureHB);                         //set health bar sprite to 0 HP HB image
        
        std::cout << "Player lost" << std::endl;
        failure.play();                                         //play sound effect for losing the game

        success = 0;                                            //player didn't win
        endOfGame(success);                                     //show death screen
    }
}

void Field::endOfGame(int success)
{
    field->clear();                                                         //clear last frame

    if(success)                                                             //if player won
    {
        textureEOGS.loadFromFile("resources/success_sprite.png");           //load success image
        textureEOGM.loadFromFile("resources/success_message.png");          //load success message image
    } else                                                                  //otherwise
    {
        textureEOGS.loadFromFile("resources/death_sprite.png");             //load death image
        textureEOGM.loadFromFile("resources/death_message.png");            //load death message image
    }

    textureEOGS.setSmooth(true);
    textureEOGM.setSmooth(true);
    spriteEOGS.setTexture(textureEOGS);                                                             //set texture of endOfGame sprite to success/death sprite
    spriteEOGM.setTexture(textureEOGM);                                                             //set texture of endOfGame message to success/death message
    spriteEOGS.setOrigin(sf::Vector2f(textureEOGS.getSize().x / 2, textureEOGS.getSize().y / 2));   //move origin of sprite (default: top left) to center of sprite
    spriteEOGS.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 3));           //set position for success/death sprite
    spriteEOGM.setOrigin(sf::Vector2f(textureEOGM.getSize().x / 2, textureEOGM.getSize().y / 2));   //move origin of sprite (default: top left) to center of sprite
    spriteEOGM.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 4 * 3));       //set position for success/death message

    //DRAW ALL ENTITIES OF ENDOFGAME SCREEN
    field->draw(spritef);
    field->draw(spritePC);
    for(int i = 0; i < amountOfTrees; i++)      //for all trees (excluding invisible mountain rectangles)
    {
        field->draw(spriteTree[i]);
    }
    field->draw(spriteHB);
    if(success) { field->draw(textscore); }     //only draw score if player won
    field->draw(spriteEOGS);
    field->draw(spriteEOGM);

    field->display();                           //display updated frame

    while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))){}     //wait until player resets or quits
        
    resetGame();                                //reset the game
}

void Field::resetGame()
{
    player.setHealthPoints(3);                              //reset HP
    player.setCollected(0);                                 //reset amount of collected Pokemon
    moves = 0;                                              //reset move counter
    textureHB.loadFromFile("resources/health_bar_3.png");   //load full health bar
    spriteHB.setTexture(textureHB);                         //set health bar sprite to full health bar image
    field->draw(spriteHB);
    playerPosX = player.spawnPX;                            //reset player position (X)
    playerPosY = player.spawnPY;                            //reset player position (Y)
    field->draw(player.spriteP);
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)                     //for all Pokemon
    {
        if(collectables[i].spriteC.getGlobalBounds().intersects(spriteCPB.getGlobalBounds()))   //if Pokemon was collected before / is placed on the CPB
        {
            collectables[i].spriteC.setScale(1, 1);                                             //enlarge Pokemon to original size
        }
        collectables[i].spriteC.setPosition(positionCX[i], positionCY[i]);                      //place Pokemon at original spawn position
    }
}

void Field::checkPositions()    //note: superiority: PokeCenter/player > trees > trainers/Pokemon - lower superiority changes position in case of an overlap. Revise this in the future to get rid of the redundancies.
{
    int done = 0;   //checks whether all entities spawned in distinct positions

    //PLAYER x POKEMON
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)     //for all Pokemon
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].spriteC.getGlobalBounds()))      //if Pokemon spawned on player
        {
            std::cout << "P x C, ";
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);     //select new random x position for Pokemon
            newPosY = collectables[i].giveRandomNumber(0,900);      //select new random y position for Pokemon
            collectables[i].spriteC.setPosition(newPosX,newPosY);   //set new position
            field->draw(collectables[i].spriteC);
            done++;
        }
    }

    //PLAYER x ENEMY
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)               //for all trainers
    {
        if(player.spriteP.getGlobalBounds().intersects(enemies[i].spriteE.getGlobalBounds()))           //if trainer spawned on player
        {
            std::cout << "P x E, ";
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);          //select new random x position for trainer
            newPosY = enemies[i].giveRandomNumber(0,900);           //select new random y position for trainer
            enemies[i].spriteE.setPosition(newPosX,newPosY);        //set new position
            field->draw(enemies[i].spriteE);
            done++;
        }
    }

    //PLAYER x TREE
    for(int i = 0; i < amountOfTrees; i++)                                      //for all trees (excluding invisible mountain rectangles)
    {
        if(player.spriteP.getGlobalBounds().intersects(spriteTree[i].getGlobalBounds()))                //if tree spawned on player
        {
            std::cout << "P x T, ";
            int newPosX,newPosY;
            newPosX = enemies[0].giveRandomNumber(0,1920);          //select new random x position for tree
            newPosY = enemies[0].giveRandomNumber(0,900);           //select new random y position for tree
            spriteTree[i].setPosition(newPosX,newPosY);             //set new position
            field->draw(spriteTree[i]);
            done++;
        }
    
    }

    //COLLECTABLE x COLLECTABLE
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)             //for all Pokemon
    {
        for(int k = i + 1; k < (sizeof(collectables)/sizeof(collectables[0])); k++)     //for all other Pokemon
        {
            if(collectables[i].spriteC.getGlobalBounds().intersects(collectables[k].spriteC.getGlobalBounds())) //if Pokemon spawned on another Pokemon
            {
                std::cout << "C x C, ";
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);     //select new random x position for Pokemon
                newPosY = collectables[i].giveRandomNumber(0,900);      //select new random y position for Pokemon
                collectables[i].spriteC.setPosition(newPosX,newPosY);   //set new position
                field->draw(collectables[i].spriteC);
                done += 1;
            }
        }
    }

    //COLLECTABLE x ENEMY
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)     //for all Pokemon
    {
        for(int k = 0; k < (sizeof(enemies)/sizeof(enemies[0])); k++)           //for all trainers
        {
            if(collectables[i].spriteC.getGlobalBounds().intersects(enemies[k].spriteE.getGlobalBounds()))      //if Pokemon spawned on trainer
            {
                std::cout << "C x E, ";
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);     //select new random x position for Pokemon
                newPosY = collectables[i].giveRandomNumber(0,900);      //select new random y position for Pokemon
                collectables[i].spriteC.setPosition(newPosX,newPosY);   //set new position
                field->draw(collectables[i].spriteC);
                done += 1;
            }
        }
    }

    //COLLECTABLE x TREE
    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)         //for all trees (including invisible mountain rectangles)
    {
        for(int k = 0; k < (sizeof(collectables)/sizeof(collectables[0])); k++) //for all Pokemon
        {
            if(spriteTree[i].getGlobalBounds().intersects(collectables[k].spriteC.getGlobalBounds()))           //if Pokemon spawned on tree
            {
                std::cout << "C x T, ";
                int newPosX,newPosY;
                newPosX = collectables[k].giveRandomNumber(0,1920);     //select new random x position for Pokemon
                newPosY = collectables[k].giveRandomNumber(0,900);      //select new random y position for Pokemon
                collectables[k].spriteC.setPosition(newPosX,newPosY);   //set new position
                field->draw(collectables[k].spriteC);
                done += 1;
            }
        }
    }

    //COLLECTABLE x POKECENTER
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)     //for all Pokemon
    {
        if(collectables[i].spriteC.getGlobalBounds().intersects(spritePC.getGlobalBounds()))        //if Pokemon spawned on PokeCenter
        {
            std::cout << "C x PC, ";
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);         //select new random x position for Pokemon
            newPosY = collectables[i].giveRandomNumber(0,900);          //select new random y position for Pokemon
            collectables[i].spriteC.setPosition(newPosX,newPosY);       //set new position
            field->draw(collectables[i].spriteC);
            done += 1;
        }
    }

    //TREE x TREE
    for(int i = 0; i < amountOfTrees; i++)              //for all trees (excluding invisible mountain rectangles)
    {
        for(int k = i + 1; k < amountOfTrees; k++)      //for all other trees (excluding invisible mountain rectangles)
        {
            if(spriteTree[i].getGlobalBounds().intersects(spriteTree[k].getGlobalBounds()))         //if tree spawned on another tree
            {
                std::cout << "T x T, ";
                int newPosX,newPosY;
                newPosX = enemies[0].giveRandomNumber(0,1920);          //select new random x position for tree
                newPosY = enemies[0].giveRandomNumber(0,900);           //select new random y position for tree
                spriteTree[i].setPosition(newPosX,newPosY);             //set new position, note: keep "i" here, issue with using spriteTree[k]: if tree spawns on invisible mountain rectangle, the rectangle will be moved instead of the tree
                field->draw(spriteTree[i]);
                done += 1;
            }
        }
    }
    
    //TREE x ENEMY
    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++) //for all trees (including invisible mountain rectangles)
    {
        for(int k = 0; k < (sizeof(enemies)/sizeof(enemies[0])); k++)   //for all trainers
        {
            if(spriteTree[i].getGlobalBounds().intersects(enemies[k].spriteE.getGlobalBounds()))    //if tree spawned on trainer  
            {
                std::cout << "T x E, ";
                int newPosX,newPosY;
                newPosX = enemies[k].giveRandomNumber(0,1920);          //select new random x position for trainer
                newPosY = enemies[k].giveRandomNumber(0,900);           //select new random y position for trainer
                enemies[k].spriteE.setPosition(newPosX,newPosY);        //set new position
                field->draw(enemies[k].spriteE);
                done += 1;
            }
        }
    }

    //TREE x POKECENTER
    for(int i = 0; i < amountOfTrees; i++)                              //for all trees (excluding invisible mountain rectangles)
    {
        if(spriteTree[i].getGlobalBounds().intersects(spritePC.getGlobalBounds()))                  //if tree spawned on PokeCenter
        {
            std::cout << "T x PC, ";
            int newPosX,newPosY;
            newPosX = enemies[0].giveRandomNumber(0,1920);              //select new random x position for trainer
            newPosY = enemies[0].giveRandomNumber(0,900);               //select new random y position for trainer
            spriteTree[i].setPosition(newPosX,newPosY);                 //set new position
            field->draw(spriteTree[i]);
            done += 1;
        }
    }

    //ENEMY x ENEMY
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)           //for all trainers
    {
        for(int k = i + 1; k < (sizeof(enemies)/sizeof(enemies[0])); k++)   //for all other trainers
        {
            if(enemies[i].spriteE.getGlobalBounds().intersects(enemies[k].spriteE.getGlobalBounds()))   //if trainer spawns on another trainer
            {
                std::cout << "E x E, ";
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);          //select new random x position for trainer
                newPosY = enemies[i].giveRandomNumber(0,900);           //select new random y position for trainer
                enemies[i].spriteE.setPosition(newPosX,newPosY);        //set new position
                field->draw(enemies[i].spriteE);
                done += 1;
            }
        }
    }

    //ENEMY x POKECENTER
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)           //for all trainers
    {
        if(enemies[i].spriteE.getGlobalBounds().intersects(spritePC.getGlobalBounds()))                 //if trainer spawns on PokeCenter
        {
            std::cout << "E x PC, ";
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);              //select new random x position for trainer
            newPosY = enemies[i].giveRandomNumber(0,900);               //select new random y position for trainer
            enemies[i].spriteE.setPosition(newPosX,newPosY);            //set new position
            field->draw(enemies[i].spriteE);
            done += 1;
        }
    }
    
    if(done != 0)               //if there were any spawn overlaps
    {
        std::cout << done << " overlap(s), determining new spawn layout" << std::endl;
        checkPositions();       //determine new spawn layout
    } else
    {
        std::cout << "Successfully loaded spawn layout" << std::endl;
    }
}
#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono>           //include all necessary external files

/*----------------------------------------------------------------


    CODE-TECHNISCH:
    -> KOMMENTARE! (gute Arbeit bis jetzt c: )
    -> Gewinner/Verloren Screen sehr ähnlich vom Ablauf-> eigene funktion?

    PRÄSENTATION:
    -> Klassendiagramm (wenn alles fertig ist)
    -> probleme und wie mans gelöst hat (zufallsmethode, usw.)
    ->

*/

Field::Field()
{
    std::cout << "Field constructor" << std::endl;
    //---------------------------------------------------------------VISUALS------------------------------------------------------------------------
    //SET VISUALS - FIELD
    //field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen);   //open a full-screen window called "Pokemon-Hunt"
    field = new sf::RenderWindow(sf::VideoMode(1920,1080), "Pokemon-Hunt");                               //open a 1920x1080 window called "Pokemon-Hunt", only use this if upper method doesn't work properly on your device (for example if secondary monitor is used)
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
    
    //SET VISUALS - HEALTH-BAR
    textureHP.loadFromFile("resources/health_bar_3.png");       //load full health bar
    textureHP.setSmooth(true);
    spriteHP.setTexture(textureHP);                             //set health bar sprite to health bar image
    spriteHP.setOrigin(sf::Vector2f(textureHP.getSize().x / 2,textureHP.getSize().y / 2));      //move origin of sprite (default: top left) to center of sprite 
    spriteHP.setPosition(1600,50);                              //place health bar sprite in the top right of the screen
    
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
    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)     //for all trees and invisible rectangles
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
    //---------------------------------------------------------------DATA------------------------------------------------------------------------     
    moves = 0;          //initialize the moves variable which is used for the score calculation
    checkPositions();   //check whether entities tried to spawn on one another when they weren't supposed to
}

Field::~Field()         //destructor
{
    std::cout << "Feld Dekonstruktor" << std::endl;
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

    if(sf::Event::Closed)                           //if window gets closed by user
    {
        field->close();                             //close everything
    }

    sf::Event event;
    
    while(field->pollEvent(event));                         //as long as any input is being made
    {
        if(InputDelayTimer.getElapsedTime() > InputDelay)   //if a certain input delay has passed
        {
            if((InputDelayTimer.getElapsedTime() > InputDelay) && ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::R)))))
            {                                               //and if any of the 6 used keys is pressed
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))   //if "Esc" is pressed
                {
                    std::cout << moves << std::endl;
                    field->close();                                     //close everything
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))        //if "R" is pressed
                {
                    resetGame();                                        //reset the game
                }

                //WASD_MOVEMENT
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
            playerPosY = 920 - (player.spriteP.getTexture()->getSize().y) / 2;
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
    field->draw(spriteHP);
    field->draw(spriteCPB);
    field->draw(spritePC);
    
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)               //for all enemies
    {
        field->draw(enemies[i].spriteE);
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)     //for all collectables
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
    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++) {
        pokeballs[i].spriteE2.setPosition(((pokeballs[i].spriteE2.getPosition().x) - pokeballs[i].speed), pokeballs[i].spriteE2.getPosition().y);
        
        if(pokeballs[i].spriteE2.getPosition().x <= -100)
        {
            int newPosY;
            newPosY = pokeballs[i].giveRandomNumber(0,900);
            pokeballs[i].speed = pokeballs[i].fRand(7.5,9.5);
            pokeballs[i].spriteE2.setPosition(1970, newPosY);
        }
    }
}

void Field::checkCollision()
{
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(enemies[i].spriteE.getGlobalBounds()))
        {
            player.setHealthPoints(player.getHealthPoints() - 1);
            player.spriteP.setPosition(sf::Vector2f(550,200));
            player.shapeP.setPosition(sf::Vector2f(550,200));
            updateHealth();
        }
    }

    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(pokeballs[i].spriteE2.getGlobalBounds()))
        {
            std::cout << "Spieler hittet Pokeball" << std::endl;
            player.setHealthPoints(player.getHealthPoints() -1);
            player.spriteP.setPosition(sf::Vector2f(550,200));
            player.shapeP.setPosition(sf::Vector2f(550,200));
            updateHealth();

        }
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].spriteC.getGlobalBounds()))
        {
            std::cout << "Collect" << std::endl;
            std::cout << player.getCollected() << std::endl;
            player.setCollected(player.getCollected() + 1);
            collectables[i].spriteC.setScale(0.5, 0.5);
            collected.play();
            //92 = spriteCPB.getPosition().x - spriteCPB.getTexture().x / 2 + 25
            //271 = spriteCPB.getPosition().x + spriteCPB.getTexture().x / 2 - 25 - collectable[0].getTexture().x - (spriteCPB.getPosition().x - spriteCPB.getTexture().x / 2 + 25)
            collectables[i].spriteC.setPosition(92 + (271/((sizeof(collectables)/sizeof(collectables[0]))-1) * (player.getCollected()-1)), 1000);
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        while(player.spriteP.getGlobalBounds().intersects(spriteTree[i].getGlobalBounds()))
        {
            std::cout << "Tree " << std::to_string(direction) << std::endl;
            switch(direction){
                case 0:
                playerPosY++;
                break;
                case 1:
                playerPosX++;
                break;
                case 2:
                playerPosY--;
                break;
                case 3:
                playerPosX--;
                break;
            }
            player.spriteP.setPosition(playerPosX, playerPosY);
        }
    }

    if(player.spriteP.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
    {
        if (player.getCollected() >= sizeof(collectables)/sizeof(collectables[0])) 
        {
            std::cout << "Gewonnen" << std::endl;
            
            field->clear();

            win.play();

            field->draw(spritef);
            field->draw(spritePC);
            for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
            {
                field->draw(spriteTree[i]);
            }

            textureSS.loadFromFile("resources/success_sprite.png");
            textureSS.setSmooth(true);
            spriteSS.setTexture(textureSS);
            spriteSS.setOrigin(sf::Vector2f(textureSS.getSize().x / 2, textureSS.getSize().y / 2));
            spriteSS.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 3));
            field->draw(spriteSS);

            textureSM.loadFromFile("resources/success_message.png");
            textureSM.setSmooth(true);
            spriteSM.setTexture(textureSM);
            spriteSM.setOrigin(sf::Vector2f(textureSM.getSize().x / 2, textureSM.getSize().y / 2));
            spriteSM.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 4 * 3));
            field->draw(spriteSM);

            score = (1150 - moves) / (4 - player.getHealthPoints());                //highest possible score: minimum of ~150 moves needed -> 1000
            if(score < 100) 
            {
                score = 100;
            }
            pokemonhollow.loadFromFile("resources/pokemon_hollow.ttf");
            textscore.setFont(pokemonhollow);
            textscore.setString("Score: " + std::to_string(score));
            textscore.setCharacterSize(96);
            textscore.setFillColor(sf::Color::Black);
            textscore.setPosition(sf::Vector2f(100, field->getSize().y / 4));
            field->draw(textscore);

            field->display();

            while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
            {   
                //std::cout << "waiting" << std::endl;
            }
            
            resetGame();
        }
    }

}

void Field::updateHealth()
{
    damage.play();
    for (int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
        {
            player.shapeP.setFillColor(sf::Color::Red);
            field->draw(player.shapeP);
            field->display();
            Sleep(100);

        } else if(i % 2 != 0)
        {
            player.shapeP.setFillColor(sf::Color::Transparent);
            field->draw(player.shapeP);
            field->display();
            Sleep(100);
        }
    }

    if(player.getHealthPoints()== 2)
    {
        textureHP.loadFromFile("resources/health_bar_2.png");
        spriteHP.setTexture(textureHP);
    } else if(player.getHealthPoints() == 1)
    {
        textureHP.loadFromFile("resources/health_bar_1.png");
        spriteHP.setTexture(textureHP);
    } else if(player.getHealthPoints() == 0)
    {
        field->clear();
        failure.play();
        field->draw(spritef);
        field->draw(spritePC);
        for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
        {
            field->draw(spriteTree[i]);
        }


        textureHP.loadFromFile("resources/health_bar_0.png");
        spriteHP.setTexture(textureHP);
        field->draw(spriteHP);

        textureDS.loadFromFile("resources/death_sprite.png");
        textureDS.setSmooth(true);
        spriteDS.setTexture(textureDS);
        spriteDS.setOrigin(sf::Vector2f(textureDS.getSize().x / 2, textureDS.getSize().y / 2));
        spriteDS.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 3));
        field->draw(spriteDS);

        textureDM.loadFromFile("resources/death_message.png");
        textureDM.setSmooth(true);
        spriteDM.setTexture(textureDM);
        spriteDM.setOrigin(sf::Vector2f(textureDM.getSize().x / 2, textureDM.getSize().y / 2));
        spriteDM.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 4 * 3));
        field->draw(spriteDM);

        field->display();

        while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
        {   
            //std::cout << "waiting" << std::endl;
        }
        
        resetGame();
    }
}

void Field::resetGame()
{
    player.setHealthPoints(3);
    player.setCollected(0);
    moves = 0;
    textureHP.loadFromFile("resources/health_bar_3.png");
    spriteHP.setTexture(textureHP);
    field->draw(spriteHP);
    playerPosX = 550;
    playerPosY = 200;
    field->draw(player.spriteP);
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(collectables[i].spriteC.getGlobalBounds().intersects(spriteCPB.getGlobalBounds()))
        {
            collectables[i].spriteC.setScale(1, 1);
        }
        collectables[i].spriteC.setPosition(positionCX[i], positionCY[i]);
    }
}

void Field::checkPositions()
{
    int done = 0;
    //PLAYER 
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].spriteC.getGlobalBounds()))
        {
            std::cout << "Player bei Collectable" << std::endl;
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);
            newPosY = collectables[i].giveRandomNumber(0,900);
            collectables[i].spriteC.setPosition(newPosX,newPosY);
            field->draw(collectables[i].spriteC);
            done += 1;
        }
    }

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(enemies[i].spriteE.getGlobalBounds()))
        {
            std::cout << "Player bei Enemy" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            field->draw(enemies[i].spriteE);
            done += 1;
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(spriteTree[i].getGlobalBounds()))
        {
            std::cout << "Player bei Baum" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            spriteTree[i].setPosition(newPosX,newPosY);
            field->draw(spriteTree[i]);
            done += 1;
        }
    
    }

    //COLLECTABLES

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        for(int k = 1; k < (sizeof(collectables)/sizeof(collectables[0])); k++)
        {
            if(i + k > sizeof(collectables)/sizeof(collectables[0]))
            {
                break;
            }
            if(collectables[i].spriteC.getGlobalBounds().intersects(collectables[i+k].spriteC.getGlobalBounds()))
            {
                std::cout << "Collectable ist bei anderem Collectable" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);
                newPosY = collectables[i].giveRandomNumber(0,900);
                collectables[i].spriteC.setPosition(newPosX,newPosY);
                field->draw(collectables[i].spriteC);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        for(int k = 0; k < (sizeof(collectables)/sizeof(collectables[0])); k++)
        {
            if(enemies[i].spriteE.getGlobalBounds().intersects(collectables[k].spriteC.getGlobalBounds()))
            {
                std::cout << "Collectable bei Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,900);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        for(int k = 0; k < (sizeof(collectables)/sizeof(collectables[0])); k++)
        {
            if(spriteTree[i].getGlobalBounds().intersects(collectables[k].spriteC.getGlobalBounds()))
            {
                std::cout << "Collectable bei Baum" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[k].giveRandomNumber(0,1920);
                newPosY = collectables[k].giveRandomNumber(0,900);
                collectables[k].spriteC.setPosition(newPosX,newPosY);
                field->draw(collectables[k].spriteC);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(collectables[i].spriteC.getGlobalBounds().intersects(spriteCPB.getGlobalBounds()) || collectables[i].spriteC.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Collectable bei PC oder CPB" << std::endl;
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);
            newPosY = collectables[i].giveRandomNumber(0,900);
            collectables[i].spriteC.setPosition(newPosX,newPosY);
            field->draw(collectables[i].spriteC);
            done += 1;
        }
    }

    //TREES

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        for(int k = 1; k < (sizeof(spriteTree)/sizeof(spriteTree[0])); k++)
        {
            if(i + k > (sizeof(spriteTree)/sizeof(spriteTree[0])))
            {
                break;
            }
            if(spriteTree[i].getGlobalBounds().intersects(spriteTree[i+k].getGlobalBounds()))
            {
                std::cout << "Baum ist bei anderem Baum" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);
                newPosY = collectables[i].giveRandomNumber(0,900);
                spriteTree[i].setPosition(newPosX,newPosY);
                field->draw(spriteTree[i]);
                done += 1;
            }
        }
    }
    
    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        for(int k = 0; k < (sizeof(enemies)/sizeof(enemies[0])); k++)
        {
            if(spriteTree[i].getGlobalBounds().intersects(enemies[k].spriteE.getGlobalBounds()))
            {
                std::cout << "Tree ist bei Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[k].giveRandomNumber(0,1920);
                newPosY = enemies[k].giveRandomNumber(0,900);
                spriteTree[i].setPosition(newPosX,newPosY);
                spriteTree[i].setPosition(newPosX,newPosY);
                field->draw(spriteTree[i]);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        if(spriteTree[i].getGlobalBounds().intersects(spriteCPB.getGlobalBounds()) || spriteTree[i].getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Tree bei PC oder CPB" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            spriteTree[i].setPosition(newPosX,newPosY);
            spriteTree[i].setPosition(newPosX,newPosY);
            field->draw(spriteTree[i]);
            done += 1;
        }
    }

    //ENEMIES

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        for(int k = 1; k < (sizeof(enemies)/sizeof(enemies[0])); k++)
        {
            if(i + k > (sizeof(enemies)/sizeof(enemies[0])))
            {
                break;
            }
            if(enemies[i].spriteE.getGlobalBounds().intersects(enemies[i+k].spriteE.getGlobalBounds()))
            {
                std::cout << "Enemy ist bei anderem Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,900);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        if(enemies[i].spriteE.getGlobalBounds().intersects(spriteCPB.getGlobalBounds()) || enemies[i].spriteE.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Enemy und PC oder CPB" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            field->draw(enemies[i].spriteE);
            done += 1;
        }
    }
    
    if(done != 0)
    {
        printf("NeuerAufruf");
        checkPositions();
    }
}


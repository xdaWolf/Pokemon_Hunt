#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono>



Field::Field()
{
    std::cout << "Field constructor" << std::endl;
    //SET VARIABLES - FIELD
    //field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen);
    field = new sf::RenderWindow(sf::VideoMode(1920,1080), "Pokemon-Hunt");
    texturef.loadFromFile("resources/backgroundv2.png");
    texturef.setSmooth(true);
    spritef.setTexture(texturef);
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2,texturef.getSize().y / 2));
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));
    //SET VARIABLES - HEALTH-BAR
    textureHP.loadFromFile("resources/health_bar_3.png");
    textureHP.setSmooth(true);
    spriteHP.setTexture(textureHP);
    spriteHP.setOrigin(sf::Vector2f(textureHP.getSize().x / 2,textureHP.getSize().y / 2));
    spriteHP.setPosition(1600,50);
    //SET VARIABLES - POKEDEX
    texturePD.loadFromFile("resources/pokedex.png");
    texturePD.setSmooth(true);
    spritePD.setTexture(texturePD);
    spritePD.setOrigin(sf::Vector2f(texturePD.getSize().x / 2,texturePD.getSize().y / 2));
    spritePD.setPosition(150,950);
    //SET VARIABLES - POKE CENTER
    texturePC.loadFromFile("resources/pokecenter.png");
    texturePC.setSmooth(true);
    spritePC.setTexture(texturePC);
    spritePC.setOrigin(sf::Vector2f(texturePC.getSize().x / 2,texturePC.getSize().y / 2));
    spritePC.setPosition(1800,500);

    checkPositions(); 
    //checkPositions();
    //checkPositions();

}

Field::~Field()
{
    std::cout << "Feld Dekonstruktor" << std::endl;
    delete field;
}

const bool Field::getFieldIsOpen() const
{
    return field->isOpen();
}

void Field::pollEvents()
{
    int playerPosX, playerPosY, movement, speed;
    playerPosX = player.spriteP.getPosition().x;
    playerPosY = player.spriteP.getPosition().y;
    
    //WALKING ANIMATION
    movement = playerPosY + playerPosX;
    speed = player.getSpeed(); //SPEED HAS TO BE ODD NUMBER!!!!!

    while (field->pollEvent(event))
    {
        //Check Events
        switch (event.type)
        {
            //Close the window if wanted
            case sf::Event::Closed:
                field->close();
                break;
            //Check if any Key is pressed
            case sf::Event::KeyPressed:
                movement++; // switch from odd to even or even to odd number (WALKING ANIMATION)
                if (event.key.code == sf::Keyboard::Escape)
                {
                    field->close();
                }
                //WASD_MOVEMENT
                if(event.key.code == sf::Keyboard::W)
                {
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png");
                    playerPosY -= speed;
                }
                else if(event.key.code == sf::Keyboard::A)
                {
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png");
                    playerPosX -= speed;
                }
                else if(event.key.code == sf::Keyboard::S)
                {
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png");
                    playerPosY += speed;
                }
                else if(event.key.code == sf::Keyboard::D)
                {
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 6) + ".png");
                    playerPosX += speed;
                }
                
        }

        //WINDOW_BORDERS
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
        if(playerPosY > (int)field->getSize().y - (player.spriteP.getTexture()->getSize().y) / 2)
        {
            playerPosY = field->getSize().y - (player.spriteP.getTexture()->getSize().y) / 2;
        }

        player.spriteP.setPosition(playerPosX, playerPosY);
        player.shapeP.setPosition(playerPosX, playerPosY);
        checkCollision();
        
    }

}

void Field::update() //manages all the game data
{
    pollEvents();
}

void Field::render() //displays the game data / game field
{
    field->clear();

    //DRAW OBJECTS
    field->draw(spritef);
    field->draw(spriteHP);
    field->draw(spritePD);
    field->draw(spritePC);
    
    for(int i = 0; i <= 5;i++)
    {
        field->draw(enemies[i].spriteE);
    }
    for(int i = 0; i <= 2;i++)
    {
        field->draw(collectables[i].spriteC);
    }
    for(int i = 0; i <= 4;i++)
    {
        field->draw(pokeballs[i].spriteE2);
    }

    field->draw(player.spriteP);

    //DISPLAY NEW WINDOW
    field->display();
}

void Field::checkCollision() // Nach animation komische Pause?! (vllt weil von hp immer abgezogen wird? vllt wegen sleep?) + Leben gehen zu schnell verloren
{
    for(int i = 0; i <= 5; i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(enemies[i].shapeE.getGlobalBounds()))
        {
            player.setHealthPoints(player.getHealthPoints() - 1);
            updateHealth();
            player.spriteP.setPosition(sf::Vector2f(1920 / 2 - 114 / 2, 1080 / 2 - 114 / 2));
        }
    }
    
    for(int i = 0; i <= 2; i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].shapeC.getGlobalBounds()))
        {
            std::cout << "Collect" << std::endl;
            if(player.getCanCollect() == 1)
            {
                player.setCanCollect(0);                
            }
            collectables[i].spriteC.setColor(sf::Color::Transparent); // Variable für jedes Collectable, wenn true -> draw, wenn nicht -> nicht drawen
        }
    }

    for(int i = 0; i <= 4; i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(pokeballs[i].shapeE2.getGlobalBounds()))
        {
            player.setHealthPoints(player.getHealthPoints() -1);
            updateHealth();
            player.spriteP.setPosition(sf::Vector2f(1920 / 2 - 114 / 2, 1080 / 2 - 114 / 2));
        }
    }

    if(player.spriteP.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
    {
        if(player.getCanCollect() == 0)
        {
            player.setCollected(player.getCollected() + 1);
            player.setCanCollect(1);
        }
    }

    checkForWin();

}

void Field::checkForWin()
{
    if(player.getCollected() == 3)
    {
        std::cout << "Gewonnen" << std::endl;
    }
}

void Field::updateHealth()
{
    for (int i = 0; i <= 2; i++)
    {
        if(i % 2 == 0)
        {
            player.shapeP.setFillColor(sf::Color::Red);
            field->draw(player.shapeP);
            field->display();
            //Sleep(200);

        } else if(i % 2 != 0)
        {
            player.shapeP.setFillColor(sf::Color::Transparent);
            field->draw(player.shapeP);
            field->display();
            //Sleep(200);
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
        //Spiel verloren;
    }

}

void Field::checkPositions()
{
    for(int i = 0; i <= 5; i++)
    {
        for(int k = 1; k <= 5; k++)
        {
            if(i + k > 5)
            {
                break;
            }
            if(enemies[i].shapeE.getGlobalBounds().intersects(enemies[i+k].shapeE.getGlobalBounds()))
            {
                std::cout << "Enemy ist bei anderem Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,1080);
                enemies[i].shapeE.setPosition(newPosX,newPosY);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
            }
        }
    }

    for(int i = 0; i <= 2; i++)
    {
        for(int k = 1; k <= 2; k++)
        {
            if(i + k > 2)
            {
                break;
            }
            if(collectables[i].shapeC.getGlobalBounds().intersects(collectables[i+k].shapeC.getGlobalBounds()))
            {
                std::cout << "Collectable ist bei anderem Collectable" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);
                newPosY = collectables[i].giveRandomNumber(0,1080);
                collectables[i].shapeC.setPosition(newPosX,newPosY);
                collectables[i].spriteC.setPosition(newPosX,newPosY);
                field->draw(collectables[i].spriteC);
            }
        }
    }
    
    for(int i = 0; i <= 5; i++)
    {
        for(int k = 0; k <= 2; k++)
        {
            if(enemies[i].shapeE.getGlobalBounds().intersects(collectables[k].shapeC.getGlobalBounds()))
            {
                std::cout << "Enemy ist bei Collectable" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,1080);
                enemies[i].shapeE.setPosition(newPosX,newPosY);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
            }
        }
    }

    for(int i = 0; i <= 5; i++)
    {
        if(player.shapeP.getGlobalBounds().intersects(enemies[i].shapeE.getGlobalBounds()))
        {
            std::cout << "Enemy ist bei Player" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,1080);
            enemies[i].shapeE.setPosition(newPosX,newPosY);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            field->draw(enemies[i].spriteE);
        }
    }

    for(int i = 0; i <= 2; i++)
    {
        if(player.shapeP.getGlobalBounds().intersects(collectables[i].shapeC.getGlobalBounds()))
        {
            std::cout << "Collectable ist bei Player" << std::endl;
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);
            newPosY = collectables[i].giveRandomNumber(0,1080);
            collectables[i].shapeC.setPosition(newPosX,newPosY);
            collectables[i].spriteC.setPosition(newPosX,newPosY);
            field->draw(collectables[i].spriteC);
        }
    }

    field->display();

}


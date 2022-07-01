#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>


Field::Field()
{
    //SET VARIABLES - FIELD
    //this->field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen);
    this->field = new sf::RenderWindow(sf::VideoMode(1920,1080), "Pokemon-Hunt");
    texturef.loadFromFile("resources/backgroundv2.png");
    texturef.setSmooth(true);
    spritef.setTexture(texturef);
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2,texturef.getSize().y / 2));
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));
    //SET VARIABLES - PLAYER
    textureHP.loadFromFile("resources/health_bar_3.png");
    textureHP.setSmooth(true);
    spriteHP.setTexture(textureHP);
    spriteHP.setOrigin(sf::Vector2f(textureHP.getSize().x / 2,textureHP.getSize().y / 2));
    spriteHP.setPosition(1600,50);

    std::cout << "Feld Konstruktor" << std::endl;

}

Field::~Field()
{
    std::cout << "Feld Dekonstruktor" << std::endl;
    delete this->field;
}

const bool Field::getFieldIsOpen() const
{
    return this->field->isOpen();
}

void Field::pollEvents()
{
    int playerPosX, playerPosY, movement, speed;
    playerPosX = player.spriteP.getPosition().x;
    playerPosY = player.spriteP.getPosition().y;
    
    //WALKING ANIMATION
    movement = playerPosY + playerPosX;
    speed = player.getSpeed(); //SPEED HAS TO BE ODD NUMBER!!!!!

    while (this->field->pollEvent(this->event))
    {
        //Check Events
        switch (this->event.type)
        {
            //Close the window if wanted
            case sf::Event::Closed:
                this->field->close();
                break;
            //Check if any Key is pressed
            case sf::Event::KeyPressed:
                movement++; // switch from odd to even or even to odd number (WALKING ANIMATION)
                if (this->event.key.code == sf::Keyboard::Escape)
                {
                    this->field->close();
                }
                //WASD_MOVEMENT
                if(this->event.key.code == sf::Keyboard::W)
                {
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png");
                    playerPosY -= speed;
                }
                else if(this->event.key.code == sf::Keyboard::A)
                {
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png");
                    playerPosX -= speed;
                }
                else if(this->event.key.code == sf::Keyboard::S)
                {
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png");
                    playerPosY += speed;
                }
                else if(this->event.key.code == sf::Keyboard::D)
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
        if(playerPosX > (int)this->field->getSize().x - (player.spriteP.getTexture()->getSize().x) / 2)
        {
            playerPosX = this->field->getSize().x - (player.spriteP.getTexture()->getSize().x) / 2;
        }
        if(playerPosY < (player.spriteP.getTexture()->getSize().y) / 2)
        {
            playerPosY = (player.spriteP.getTexture()->getSize().y) / 2;
        }
        if(playerPosY > (int)this->field->getSize().y - (player.spriteP.getTexture()->getSize().y) / 2)
        {
            playerPosY = this->field->getSize().y - (player.spriteP.getTexture()->getSize().y) / 2;
        }

        player.spriteP.setPosition(playerPosX, playerPosY);
        
    }

}

void Field::update() //manages all the game data
{
    this->pollEvents();
}

void Field::render() //displays the game data / game field
{
    
    this->field->clear();

    //DRAW OBJECTS
    this->field->draw(spritef);
    this->field->draw(spriteHP);
    this->field->draw(enemy1.getSprite());
    this->field->draw(enemy2.getSprite());
    this->field->draw(enemy3.getSprite());
    this->field->draw(collect1.getSprite());
    this->field->draw(collect2.getSprite());
    this->field->draw(collect3.getSprite());
    this->field->draw(player.spriteP);

    //DISPLAY NEW WINDOW
    this->field->display();
}


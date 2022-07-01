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

    this->field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen);
    texturef.loadFromFile("resources/backgroundv2.png");
    texturef.setSmooth(true);
    spritef.setTexture(texturef);
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2,texturef.getSize().y / 2));
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));
    
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
        int playerPosX, playerPosY;
        playerPosX = player.spriteP.getPosition().x;
        playerPosY = player.spriteP.getPosition().y;

    while (this->field->pollEvent(this->event))
        {
            
            //Check Events
            switch (this->event.type)
            {
                //Close the window if wanted
                case sf::Event::Closed:
                    this->field->close();
                    break;
                case sf::Event::KeyPressed:
                    if (this->event.key.code == sf::Keyboard::Escape)
                        this->field->close();
                    if(this->event.key.code == sf::Keyboard::W)
                    {
                        player.setTexture("resources/pikachu_back_1.png");
                        playerPosY = playerPosY - 10;
                    }
                    if(this->event.key.code == sf::Keyboard::A)
                    {
                        player.setTexture("resources/pikachu_left_1.png");
                        playerPosX = playerPosX - 10;
                    }
                    if(this->event.key.code == sf::Keyboard::S)
                    {
                        player.setTexture("resources/pikachu_forward_1.png");
                        playerPosY = playerPosY + 10;
                    }
                    if(this->event.key.code == sf::Keyboard::D)
                    {
                        player.setTexture("resources/pikachu_right_1.png");
                        playerPosX = playerPosX + 10;
                    }
                    
            }

            if(playerPosX < 0)
            {
                playerPosX = 0;
            }
            if(playerPosX > (int)this->field->getSize().x)
            {
                playerPosX = this->field->getSize().x;
            }
            if(playerPosY < 0)
            {
                playerPosY = 0;
            }
            if(playerPosY > (int)this->field->getSize().y)
            {
                playerPosY = this->field->getSize().y;
            }

            player.spriteP.setPosition(playerPosX, playerPosY);
            //player.setPosition()
            std::cout << "Position gesetzt" << std::endl;
        }


}

void Field::update() //manages all the game data
{
    this->pollEvents();
}

void Field::render() //displays the game data / game field
{
    /*
        Renders the game field
    */
    
    this->field->clear();


    this->field->draw(spritef);
    this->field->draw(enemy1.getSprite());
    this->field->draw(enemy2.getSprite());
    this->field->draw(enemy3.getSprite());
    this->field->draw(player.getSprite());
    //Draw game objects
    this->field->display();
}


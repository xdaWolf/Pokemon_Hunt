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

    this->field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt");
    //texture = new sf::Texture(); //??????
    //sprite = new sf::Sprite();
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
                        std::cout << "W wurde gedrückt!" << std::endl;
                        //this->player.getSprite().getPosition().y -= 10;
                        //this->player.getSprite().setPosition(this->player.getSprite().getPosition().x, this->player.getSprite().getPosition().y);
                    break;

            }
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


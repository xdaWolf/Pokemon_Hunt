#include "field.h"

Field::Field()
{
    this->field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt");
    //texture = new sf::Texture(); //??????
    //sprite = new sf::Sprite();
    texture.loadFromFile("resources/backgroundv1.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2,texture.getSize().y / 2));
    sprite.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));

}

Field::~Field()
{
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
    
    /*this->field->clear();*/

    this->field->draw(sprite);
    this->field->draw(enemy1);
    //Draw game objects
    this->field->display();
}


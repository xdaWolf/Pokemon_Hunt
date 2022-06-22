#include "field.h"
class Game;

Field::Field()
{

    this->field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt");
    //texture = new sf::Texture(); //??????
    //sprite = new sf::Sprite();
    texturef.loadFromFile("resources/backgroundv1.png");
    texturef.setSmooth(true);
    spritef.setTexture(texturef);
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2,texturef.getSize().y / 2));
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));

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
    
    this->field->clear();

    this->field->draw(spritef);
    //this->field->draw(Game.getEnemy1().getSprite());
    //Draw game objects
    this->field->display();
}


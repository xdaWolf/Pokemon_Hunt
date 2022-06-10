#include "game.h"

//private functions

void Game::initVariables()
{
    // init variables
    this->window = nullptr;

}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt");
    //texture = new sf::Texture(); //??????
    //sprite = new sf::Sprite();
    texture.loadFromFile("backgroundv1.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2,texture.getSize().y / 2));
    sprite.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
}

//Constructor / Destructor

Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

//get-Methods

const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

// public functions

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
        {
            //Check Events
            switch (this->event.type)
            {
                //Close the window if wanted
                case sf::Event::Closed:
                    this->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (this->event.key.code == sf::Keyboard::Escape)
                        this->window->close();
                    break;

            }
        }


}

void Game::update() //manages all the game data
{


    this->pollEvents();
}

void Game::render() //displays the game data / game field
{
    /*
        Renders the game field
    */
    
    /*this->window->clear();*/

    this->window->draw(sprite);
    //Draw game objects
    this->window->display();
}


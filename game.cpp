#include "game.h"

//private functions

void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Titlebar | sf::Style::Default);
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
    
    this->window->clear(sf::Color(0,0,255,255));

    //Draw game objects
    this->window->display();
}


#include "Menu.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

Menu::Menu() : BaseEntity() // constructor
{
    std::cout << "Menu constructor" << std::endl;
    setTexture("resources/pause_menu.png");
    initializeSpriteAndTexture();
}

void Menu::initializeSpriteAndTexture()
{
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    sprite.setPosition(960, 540);                                                                             // place menu in the middle of the screen
    sprite.setOrigin(sf::Vector2f(this->getTexture()->getSize().x / 2, this->getTexture()->getSize().y / 2)); // move origin of sprite (default: top left) to center of sprite
}

Menu::~Menu()
{
} // destructor

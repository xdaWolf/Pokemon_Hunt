#include "Menu.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h> //include all necessary external files

Menu::Menu() : BaseEntity() // constructor
{
    std::cout << "Menu constructor" << std::endl;
    setTexture("resources/pause_menu.png");
    initializeSpriteAndTexture();
    initializeText();
    initializeButtons();
}

Menu::~Menu() {} // destructor

void Menu::initializeSpriteAndTexture()
{
    const_cast<Texture *>(this->getTexture())->setSmooth(true);
    sf::Vector2u textureSize = this->getTexture()->getSize();
    sprite.setPosition(textureSize.x / 2, textureSize.y / 2);
    sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
}

void Menu::initializeText() // initialize text for buttons
{
    if (!font_menu.loadFromFile("resources/pokemon_hollow.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }

    initializeButtonText(text_mode, "Mode:", 50, 1250, 200); // set button text and position
    initializeButtonText(text_difficulty, "Difficulty:", 50, 1310, 500);
    initializeButtonText(text_volume, "Volume:", 50, 1270, 830);

    initializeButtonText(button_mode1.label, "Normal", 40, 1312, 350);
    initializeButtonText(button_mode2.label, "Survival", 40, 1662, 350);
    initializeButtonText(button_difficulty1.label, "Easy", 40, 1262, 650);
    initializeButtonText(button_difficulty2.label, "Normal", 40, 1487, 650);
    initializeButtonText(button_difficulty3.label, "Hard", 40, 1712, 650);
}

void Menu::initializeButtonText(sf::Text &pText, const std::string &pContent, int pCharacterSize, float pPosX, float pPosY) // initialize text object
{
    pText.setString(pContent); // set properties of text object
    pText.setFont(font_menu);
    pText.setCharacterSize(pCharacterSize);
    pText.setPosition(pPosX, pPosY);
    pText.setFillColor(sf::Color::Black);
    pText.setOrigin(pText.getGlobalBounds().width / 2, pText.getGlobalBounds().height / 2);
}

void Menu::initializeButtons()
{
    initializeButton(button_mode1, 1175, 300, 275, 100); // set properties of button objects
    initializeButton(button_mode2, 1525, 300, 275, 100);
    initializeButton(button_difficulty1, 1175, 600, 175, 100);
    initializeButton(button_difficulty2, 1400, 600, 175, 100);
    initializeButton(button_difficulty3, 1625, 600, 175, 100);

    slider_volume.setSize(sf::Vector2f(400, 25));
    slider_volume.setPosition(1400, 825);
    slider_volume.setFillColor(sf::Color::Black);

    sliderhandle_volume.setSize(sf::Vector2f(25, 50));
    sliderhandle_volume.setPosition(1400, 812.5);
    sliderhandle_volume.setFillColor(sf::Color(248, 208, 80, 255));
    sliderhandle_volume.setOutlineThickness(4.f);
    sliderhandle_volume.setOutlineColor(sf::Color::Transparent);
}

void Menu::initializeButton(Button &pButton, float pPosX, float pPosY, float pWidth, float pHeight) // initialize button object
{
    pButton.setSize(sf::Vector2f(pWidth, pHeight));
    pButton.setPosition(pPosX, pPosY);
    pButton.setFillColor(sf::Color::Transparent);
    pButton.setOutlineThickness(5.f);
    pButton.setOutlineColor(sf::Color(248, 208, 80, 255));
}

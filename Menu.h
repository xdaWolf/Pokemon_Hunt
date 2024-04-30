#pragma once

#include "BaseEntity.h"
#include "Button.h"

#ifndef MENU_H_
#define MENU_H_
using namespace sf;
/*
    Menu class: Class for menu that is shown when pressing m. Holds Buttons that can change gamemode
*/

class Menu : public BaseEntity
{
private:
    // VARIABLES
    Font font_menu;
    Text text_mode1, text_mode2, text_difficulty1, text_difficulty2, text_difficulty3;
    // METHODS
    void initializeButtonText(sf::Text &pText, const std::string &pContent, int pCharacterSize, float pPosX, float pPosY);
    void initializeButton(Button &pButton, float pPosX, float pPosY, float pWidth, float pHeight);

public:
    // VARIABLES
    Button button_mode1, button_mode2, button_difficulty1, button_difficulty2, button_difficulty3, slider_volume, sliderhandle_volume;
    Text text_mode, text_difficulty, text_volume;

    // METHODS
    Menu();  // constructor
    ~Menu(); // destructor

    void initializeSpriteAndTexture() override;
    void initializeText();    // initializes text for shown menu
    void initializeButtons(); // initializes buttons for shown menu
};

#endif
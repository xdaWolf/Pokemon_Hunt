#pragma once

#include <SFML/Graphics.hpp>

#ifndef BUTTON_H_
#define BUTTON_H_
using namespace sf;
/*
    Button class: Class for Buttons that are used in Menu
*/

class Button : public RectangleShape
{
private:
    // VARIABLES
    sf::Font font;

public:
    // VARIABLES
    sf::Text label;

    // METHODS
    Button();  // constructor
    ~Button(); // destructor

    void setText(const std::string &pText);
    void setFont(const sf::Font &pFont);
    const sf::Text &getText() const;
};

#endif
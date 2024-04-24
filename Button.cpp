#include "Button.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono> //include all necessary external files

Button::Button() // constructor
{
    std::cout << "Button constructor" << std::endl;
}

Button::~Button() // destructor
{
}

void Button::setText(const std::string &text)
{
    label.setString(text);
    label.setPosition(getPosition().x + getSize().x / 2 - label.getGlobalBounds().width / 2, getPosition().y + getSize().y / 2 - label.getGlobalBounds().height / 2); // place text in the center of the button
}

void Button::setFont(const sf::Font &font)
{
    this->font = font;
    label.setFont(font);
}

const sf::Text &Button::getText() const
{
    return label;
}

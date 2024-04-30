#include "doctest.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

// Test case for the Button class
TEST_CASE("Button Tests")
{
    // Create a font for testing
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Load a font file for testing

    // Create a Button object for testing
    Button button;

    SUBCASE("SetText")
    {
        // Set text for the button
        button.setText("Click Me");

        // Check if the text is set correctly
        CHECK(button.getText().getString() == "Click Me");
    }

    SUBCASE("SetFont")
    {
        // Set font for the button
        button.setFont(font);

        // Check if the font is set correctly
        CHECK(button.getText().getFont() == &font);
    }

    SUBCASE("TextPosition")
    {
        // Set font for the button
        button.setFont(font);

        // Set text for the button
        button.setText("Centered Text");

        // Get button position
        sf::Vector2f buttonPosition = button.getPosition();

        // Get button size
        sf::Vector2f buttonSize = button.getSize();

        // Calculate expected text position
        float expectedX = buttonPosition.x + buttonSize.x / 2 - button.getText().getGlobalBounds().width / 2;
        float expectedY = buttonPosition.y + buttonSize.y / 2 - button.getText().getGlobalBounds().height / 2;

        // Check if the text is correctly centered on the button
        CHECK(button.getText().getPosition().x == doctest::Approx(expectedX));
        CHECK(button.getText().getPosition().y == doctest::Approx(expectedY));
    }
}

#include "doctest.h"
#include "Menu.h"

TEST_CASE("Menu constructor initializes correctly")
{
    Menu menu;
    const sf::Texture *texture = menu.getTexture();
    REQUIRE(texture != nullptr);
}

TEST_CASE("initializeSpriteAndTexture initializes sprite and texture correctly")
{
    Menu menu;
    menu.initializeSpriteAndTexture();
    const sf::Sprite &sprite = menu.sprite;
    REQUIRE(sprite.getTexture() != nullptr);
}

TEST_CASE("initializeText initializes text correctly")
{
    Menu menu;
    menu.initializeText();
    CHECK(menu.text_mode.getString() == "Mode:");
}

TEST_CASE("initializeButtons initializes buttons correctly")
{
    Menu menu;
    menu.initializeButtons();
    CHECK(menu.button_mode1.getSize() == sf::Vector2f(275, 100));
}

#include "doctest.h"
#include "NormalGameMode.h"
#include "Field.h"
#include <memory>

TEST_CASE("NormalGameMode Update Tests")
{
    SUBCASE("UpdateWithoutInput")
    {
        Field field;
        NormalGameMode normalGameMode(&field);

        normalGameMode.update();

        // Check if player position is initialized correctly
        CHECK(field.playerPosX == field.player.sprite.getPosition().x);
        CHECK(field.playerPosY == field.player.sprite.getPosition().y);

        // Check if menu is not open initially
        CHECK(field.menuIsOpen == false);
    }
}

TEST_CASE("NormalGameMode Render Tests")
{
    SUBCASE("Render")
    {
        Field field;
        NormalGameMode normalGameMode(&field);

        field.window_field = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Test Window");

        // Simulate render call
        normalGameMode.render();

        // Check if window is cleared and updated
        CHECK(field.window_field->isOpen());
    }
}

#include "doctest.h"
#include "SurvivalGameMode.h"
#include "Field.h"

TEST_CASE("SurvivalGameMode Update Tests")
{
    SUBCASE("UpdateWithoutInput")
    {
        Field field;
        SurvivalGameMode survivalGameMode(&field);

        survivalGameMode.update();

        // Check if player position is initialized correctly
        CHECK(field.playerPosX == field.player.sprite.getPosition().x);
        CHECK(field.playerPosY == field.player.sprite.getPosition().y);

        // Check if menu is not open initially
        CHECK(field.menuIsOpen == false);
    }
}

TEST_CASE("SurvivalGameMode Render Tests")
{
    SUBCASE("Render")
    {
        Field field;
        SurvivalGameMode survivalGameMode(&field);

        // Mock some necessary methods for rendering
        field.window_field = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Test Window");

        // Simulate render call
        survivalGameMode.render();

        // Check if window is cleared and updated
        CHECK(field.window_field->isOpen());
    }
}

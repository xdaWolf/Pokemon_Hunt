#include "doctest.h"
#include "Field.h"

TEST_CASE("Field construction")
{
    Field field;

    SUBCASE("Field window is open")
    {
        CHECK(field.getFieldIsOpen() == true);
    }

    SUBCASE("Menu is closed by default")
    {
        CHECK(field.menuIsOpen == false);
    }
}

TEST_CASE("Collision detection")
{
    Field field;
    field.attach(&field.player); // attach player to field

    SUBCASE("Player collides with trainer")
    {
        // set player and trainer on the same position
        field.player.sprite.setPosition(100, 100);
        field.trainers[0].sprite.setPosition(100, 100);

        field.checkCollision();
        CHECK(field.player.getHealthPoints() == 2); // player should lose health points
    }

    SUBCASE("Player collides with collectable")
    {
        // set player and collectable on the same position
        field.player.sprite.setPosition(100, 100);
        field.collectables[0].sprite.setPosition(100, 100);

        field.checkCollision();
        CHECK(field.player.getCollected() == 1); // player should collect the collectable
    }
}

TEST_CASE("Menu behavior")
{
    Field field;

    SUBCASE("Open menu")
    {
        field.openMenu();
        CHECK(field.menuIsOpen == true);
    }

    SUBCASE("Close menu")
    {
        field.openMenu(); // open menu
        field.closeMenu();
        CHECK(field.menuIsOpen == false);
    }
}

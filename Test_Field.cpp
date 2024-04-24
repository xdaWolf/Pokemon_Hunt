#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "doctest.h"
#include "trompeloeil.hpp"
#include "Field.h"

using trompeloeil::_;

// Mock-Klasse für sf::Sprite
class MockSprite : public sf::Sprite
{
public:
    MAKE_MOCK2(setPosition, void(float x, float y));
};

class MockPlayer : public Player
{
public:
    MAKE_MOCK0(getHealthPoints, int());
};

class MockField : public Field
{
public:
    MAKE_MOCK0(getFieldIsOpen, bool(), const);
    MAKE_MOCK1(changeGamemode, void(int));
    MAKE_MOCK1(attach, void(Player *));
    MAKE_MOCK0(checkCollision, void());
    MAKE_MOCK0(openMenu, void());
    MAKE_MOCK0(closeMenu, void());

    // Mock-Objekte für die Sprite-Objekte in Field
    MockSprite playerSprite;
    MockSprite trainerSprite;
    MockPlayer player;
};

TEST_CASE("Field construction")
{
    MockField field;

    REQUIRE_CALL(field, getFieldIsOpen())
        .RETURN(true);

    CHECK(field.getFieldIsOpen());
    CHECK_FALSE(field.menuIsOpen);
}

TEST_CASE("Change gamemode")
{
    MockField field;

    REQUIRE_CALL(field, changeGamemode(1));
    field.changeGamemode(1);

    REQUIRE_CALL(field, changeGamemode(0));
    field.changeGamemode(0);
}

TEST_CASE("Collision detection")
{
    MockField field;

    REQUIRE_CALL(field, attach(_));
    REQUIRE_CALL(field.playerSprite, setPosition(100, 100));
    REQUIRE_CALL(field.trainerSprite, setPosition(100, 100));
    REQUIRE_CALL(field, checkCollision());
    REQUIRE_CALL(field.player, getHealthPoints())
        .RETURN(2);

    field.attach(&field.player);
    field.playerSprite.setPosition(100, 100);
    field.trainerSprite.setPosition(100, 100);
    field.gamemode = 0;
    field.checkCollision();
    CHECK(field.player.getHealthPoints() == 2);
}

TEST_CASE("Menu behavior")
{
    MockField field;

    REQUIRE_CALL(field, openMenu());
    REQUIRE_CALL(field, getMenuIsOpen())
        .RETURN(true);
    field.openMenu();
    CHECK(field.getMenuIsOpen());

    REQUIRE_CALL(field, openMenu());
    REQUIRE_CALL(field, closeMenu());
    REQUIRE_CALL(field, getMenuIsOpen())
        .RETURN(false);
    field.openMenu();
    field.closeMenu();
    CHECK_FALSE(field.getMenuIsOpen());
}

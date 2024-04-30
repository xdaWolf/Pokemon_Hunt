#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "doctest.h"

TEST_CASE("Constructor initializes player correctly")
{
    Player player;
    CHECK(player.getHealthPoints() == 3);
    CHECK(player.getSpeed() == 9);
    CHECK(player.getCollected() == 0);
}

TEST_CASE("initializeSpriteAndTexture initializes player sprite and texture correctly")
{
    Player player;
    player.initializeSpriteAndTexture();
    CHECK(player.getTexture()->isSmooth() == true);
}

TEST_CASE("refresh updates player attributes correctly")
{
    Player player;
    player.refresh(100, 50, 10);
    CHECK(player.getHealthPoints() == 100);
    CHECK(player.getSpeed() == 50);
    CHECK(player.getCollected() == 10);
}

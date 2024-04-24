#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "doctest.h"

// Testet, ob der Konstruktor die Textur richtig setzt und den Spieler initialisiert
TEST_CASE("Constructor initializes player correctly")
{
    Player player;
    CHECK(player.getHealthPoints() == 3);
    CHECK(player.getSpeed() == 9);
    CHECK(player.getCollected() == 0);
}

// Testet, ob die Methode initializeSpriteAndTexture die Sprite- und Texturattribute des Spielers richtig initialisiert
TEST_CASE("initializeSpriteAndTexture initializes player sprite and texture correctly")
{
    Player player;
    player.initializeSpriteAndTexture();
    CHECK(player.getTexture()->isSmooth() == true);
    // Weitere Tests, um sicherzustellen, dass die Methode die Sprite- und Texturattribute korrekt initialisiert
}

// Testet, ob die Methode refresh die Attribute des Spielers richtig aktualisiert
TEST_CASE("refresh updates player attributes correctly")
{
    Player player;
    player.refresh(100, 50, 10);
    CHECK(player.getHealthPoints() == 100);
    CHECK(player.getSpeed() == 50);
    CHECK(player.getCollected() == 10);
}

// Weitere Tests können hinzugefügt werden, um sicherzustellen, dass alle Methoden korrekt funktionieren

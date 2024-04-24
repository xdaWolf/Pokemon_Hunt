#include "doctest.h"
#include "Menu.h"

TEST_CASE("Menu constructor initializes correctly")
{
    Menu menu;
    const sf::Texture *texture = menu.getTexture();
    REQUIRE(texture != nullptr);
    // Hier können weitere Tests hinzugefügt werden, um sicherzustellen, dass die Initialisierung korrekt ist
}

TEST_CASE("initializeSpriteAndTexture initializes sprite and texture correctly")
{
    Menu menu;
    menu.initializeSpriteAndTexture();
    const sf::Sprite &sprite = menu.sprite;
    REQUIRE(sprite.getTexture() != nullptr);
    // Hier können weitere Tests hinzugefügt werden, um sicherzustellen, dass Sprite und Texture korrekt initialisiert wurden
}

TEST_CASE("initializeText initializes text correctly")
{
    Menu menu;
    menu.initializeText();
    // Hier können Tests hinzugefügt werden, um sicherzustellen, dass Textobjekte korrekt initialisiert wurden
    CHECK(menu.text_mode.getString() == "Mode:");
    // Weitere Tests für andere Textobjekte
}

TEST_CASE("initializeButtons initializes buttons correctly")
{
    Menu menu;
    menu.initializeButtons();
    // Hier können Tests hinzugefügt werden, um sicherzustellen, dass Button-Objekte korrekt initialisiert wurden
    CHECK(menu.button_mode1.getSize() == sf::Vector2f(275, 100));
    // Weitere Tests für andere Button-Objekte
}

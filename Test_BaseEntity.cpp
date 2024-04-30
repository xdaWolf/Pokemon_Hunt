#include "doctest.h"
#include "BaseEntity.h"

TEST_CASE("setTexture loads texture correctly")
{
    BaseEntity entity;
    entity.setTexture("resources/enemy_1.png");
    const sf::Texture *texture = entity.getTexture();
    REQUIRE(texture != nullptr);
}

TEST_CASE("initializeSpriteAndTexture initializes sprite and texture correctly")
{
    BaseEntity entity;
    entity.setTexture("resources/enemy_1.png");
    entity.initializeSpriteAndTexture();
    const sf::Sprite &sprite = entity.sprite;
    REQUIRE(sprite.getTexture() != nullptr);
}

TEST_CASE("giveRandomNumber returns correct random number")
{
    BaseEntity entity;
    int randomNumber = entity.giveRandomNumber(0, 10);
    CHECK(randomNumber >= 0);
    CHECK(randomNumber <= 10);
}

TEST_CASE("giveRandomDouble returns correct random double")
{
    BaseEntity entity;
    double randomDouble = entity.giveRandomDouble(0.0, 1.0);
    CHECK(randomDouble >= 0.0);
    CHECK(randomDouble <= 1.0);
}

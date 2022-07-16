#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono>

/*----------------------------------------------------------------
    Letzte Änderungen:
    -> nur ein mal werden Leben verloren
    -> in enemy2 random funktion, die eigentlich werte zwischen 0.3 und 2.0 geben soll (als speed-Möglichkeiten für Pokebälle)
    -> Variable invulnerable (Spieler) soll angeben, ob er unverwundbar ist (0 = Nein, 1 = Ja) und dem Spieler einen kurzzeitigen Schutz geben, wenn er getroffen wurde
    
    TO-DO
    -> Unerreichbare Bereiche (Grenzen neu machen) einfügen (Berg bzw. Bäume unten)
    -> Spawn-Schutz
    -> Collectables müssen vom Spielfeld verschwinden (gelöscht werden) nachdem diese eingesammelt wurden (und abgegeben wurden? -> verliert man alle, wenn man stirbt?)
    -> vielleicht neue random-Funktion?!
    -> Unten im Pokedex soll angezeigt werden welche Pokemon und wie viele man eingesammelt hat
    -> den Pokecenter vielleicht überarbeiten (Position (soll random an einer stelle am Rand der map erscheinen, wenn man ein collectable hat?)
    -> 


*/

Field::Field()
{
    std::cout << "Field constructor" << std::endl;
    //SET VARIABLES - FIELD
    //field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen);
    field = new sf::RenderWindow(sf::VideoMode(1920,1080), "Pokemon-Hunt");
    texturef.loadFromFile("resources/backgroundv2.png");
    texturef.setSmooth(true);
    spritef.setTexture(texturef);
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2,texturef.getSize().y / 2));
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));
    //SET VARIABLES - HEALTH-BAR
    textureHP.loadFromFile("resources/health_bar_3.png");
    textureHP.setSmooth(true);
    spriteHP.setTexture(textureHP);
    spriteHP.setOrigin(sf::Vector2f(textureHP.getSize().x / 2,textureHP.getSize().y / 2));
    spriteHP.setPosition(1600,50);
    //SET VARIABLES - POKEDEX
    texturePD.loadFromFile("resources/pokedex.png");
    texturePD.setSmooth(true);
    spritePD.setTexture(texturePD);
    spritePD.setOrigin(sf::Vector2f(texturePD.getSize().x / 2,texturePD.getSize().y / 2));
    spritePD.setPosition(150,950);
    //SET VARIABLES - POKE CENTER
    texturePC.loadFromFile("resources/pokecenter.png");
    texturePC.setSmooth(true);
    spritePC.setTexture(texturePC);
    spritePC.setOrigin(sf::Vector2f(texturePC.getSize().x / 2,texturePC.getSize().y / 2));
    spritePC.setPosition(1800,500);
    //SET VARIABLES - TREES
    for(int i = 0; i <= 3; i++)
    {
        textureTree[i].loadFromFile("resources/tree.png");
        textureTree[i].setSmooth(true);
        spriteTree[i].setTexture(textureTree[i]);
        spriteTree[i].setOrigin(sf::Vector2f(textureTree[i].getSize().x / 2, textureTree[i].getSize().y / 2));
        spriteTree[i].setPosition(enemies[0].giveRandomNumber(0,1920), enemies[0].giveRandomNumber(0,1080));
    }    
    checkPositions();
    checkPositions();

}

Field::~Field()
{
    std::cout << "Feld Dekonstruktor" << std::endl;
    delete field;
}

const bool Field::getFieldIsOpen() const
{
    return field->isOpen();
}


void Field::update() //manages all the game data
{
    int playerPosX, playerPosY, movement, speed;
    playerPosX = player.spriteP.getPosition().x;
    playerPosY = player.spriteP.getPosition().y;
    
    //WALKING ANIMATION
    movement = playerPosY + playerPosX;
    speed = player.getSpeed(); //SPEED HAS TO BE ODD NUMBER!!!!!

    
    //Close the window if wanted
    
    if(sf::Event::Closed)
    {
        field->close();

    }
    
    //Check if any Key is pressed
    
    //movement++; // switch from odd to even or even to odd number (WALKING ANIMATION)

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        field->close();
    }
    //WASD_MOVEMENT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png");
        movement++;
        playerPosY -= speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png");
        movement++;
        playerPosX -= speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png");
        movement++;
        playerPosY += speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 6) + ".png");
        movement++;
        playerPosX += speed;
    }
        
    //WINDOW_BORDERS
    if(playerPosX < (player.spriteP.getTexture()->getSize().x) / 2)
    {
        playerPosX = (player.spriteP.getTexture()->getSize().x) / 2;
    }
    if(playerPosX > (int)field->getSize().x - (player.spriteP.getTexture()->getSize().x) / 2)
    {
        playerPosX = field->getSize().x - (player.spriteP.getTexture()->getSize().x) / 2;
    }
    if(playerPosY < (player.spriteP.getTexture()->getSize().y) / 2)
    {
        playerPosY = (player.spriteP.getTexture()->getSize().y) / 2;
    }
    if(playerPosY > (int)field->getSize().y - (player.spriteP.getTexture()->getSize().y) / 2)
    {
        playerPosY = field->getSize().y - (player.spriteP.getTexture()->getSize().y) / 2;
    }

    player.spriteP.setPosition(playerPosX, playerPosY);
    player.shapeP.setPosition(playerPosX, playerPosY);
    
}

void Field::render() //displays the game data / game field
{
    field->clear();

    //DRAW OBJECTS
    field->draw(spritef);
    field->draw(spriteHP);
    field->draw(spritePD);
    field->draw(spritePC);
    
    for(int i = 0; i <= 5;i++)
    {
        field->draw(enemies[i].spriteE);
    }
    for(int i = 0; i <= 2;i++)
    {
        if(collectables[i].collected == 0)
        {
            field->draw(collectables[i].spriteC);
        }
    }
    
    for(int i = 0; i <= 4;i++)
    {
        field->draw(pokeballs[i].spriteE2);
    }

    for(int i = 0; i <= 3;i++)
    {
        field->draw(spriteTree[i]);
    }
    field->draw(player.spriteP);

    pokeballMovement();
    checkCollision();

    //DISPLAY NEW WINDOW
    field->display();
}

void Field::pokeballMovement()
{
    
    pokeballs[0].spriteE2.setPosition(((pokeballs[0].spriteE2.getPosition().x) - pokeballs[0].speed), pokeballs[0].spriteE2.getPosition().y);
    pokeballs[0].shapeE2.setPosition(((pokeballs[0].spriteE2.getPosition().x) - pokeballs[0].speed), pokeballs[0].spriteE2.getPosition().y);
    
    if(pokeballs[0].spriteE2.getPosition().x <= -100)
    {
        int newPosY;
        newPosY = pokeballs[0].giveRandomNumber(0,1080);
        pokeballs[0].speed = pokeballs[0].fRand(1.5,3.5);
        pokeballs[0].spriteE2.setPosition(1970, newPosY);
        pokeballs[0].shapeE2.setPosition(1970, newPosY);
    }

    pokeballs[1].spriteE2.setPosition(((pokeballs[1].spriteE2.getPosition().x) - pokeballs[1].speed), pokeballs[1].spriteE2.getPosition().y);
    pokeballs[1].shapeE2.setPosition(((pokeballs[1].spriteE2.getPosition().x) - pokeballs[1].speed), pokeballs[1].spriteE2.getPosition().y);
    
    if(pokeballs[1].spriteE2.getPosition().x <= -100)
    {
        int newPosY;
        newPosY = pokeballs[1].giveRandomNumber(0,1080);
        pokeballs[1].speed = pokeballs[1].fRand(1.5,3.5);
        pokeballs[1].spriteE2.setPosition(1970, newPosY);
        pokeballs[1].shapeE2.setPosition(1970, newPosY);
    }

    pokeballs[2].spriteE2.setPosition(((pokeballs[2].spriteE2.getPosition().x) - pokeballs[2].speed), pokeballs[2].spriteE2.getPosition().y);
    pokeballs[2].shapeE2.setPosition(((pokeballs[2].spriteE2.getPosition().x) - pokeballs[2].speed), pokeballs[2].spriteE2.getPosition().y);
    
    if(pokeballs[2].spriteE2.getPosition().x <= -100)
    {
        int newPosY;
        newPosY = pokeballs[2].giveRandomNumber(0,1080);
        pokeballs[2].speed = pokeballs[2].fRand(1.5,3.5);
        pokeballs[2].spriteE2.setPosition(19570, newPosY);
        pokeballs[2].shapeE2.setPosition(1970, newPosY);
    }
    
    pokeballs[3].spriteE2.setPosition(((pokeballs[3].spriteE2.getPosition().x) - pokeballs[3].speed), pokeballs[3].spriteE2.getPosition().y);
    pokeballs[3].shapeE2.setPosition(((pokeballs[3].spriteE2.getPosition().x) - pokeballs[3].speed), pokeballs[3].spriteE2.getPosition().y);
    
    if(pokeballs[3].spriteE2.getPosition().x <= -100)
    {
        int newPosY;
        newPosY = pokeballs[3].giveRandomNumber(0,1080);
        pokeballs[3].speed = pokeballs[3].fRand(1.5,3.5);
        pokeballs[3].spriteE2.setPosition(1970, newPosY);
        pokeballs[3].shapeE2.setPosition(1970, newPosY);
    }
    
    pokeballs[4].spriteE2.setPosition(((pokeballs[4].spriteE2.getPosition().x) - pokeballs[4].speed), pokeballs[4].spriteE2.getPosition().y);
    pokeballs[4].shapeE2.setPosition(((pokeballs[4].spriteE2.getPosition().x) - pokeballs[4].speed), pokeballs[4].spriteE2.getPosition().y);
    
    if(pokeballs[4].spriteE2.getPosition().x <= -100)
    {
        int newPosY;
        newPosY = pokeballs[4].giveRandomNumber(0,1080);
        pokeballs[4].speed = pokeballs[4].fRand(1.5,3.5);
        pokeballs[4].spriteE2.setPosition(1970, newPosY);
        pokeballs[4].shapeE2.setPosition(1970, newPosY);
    }
}

void Field::checkCollision()
{
    if(player.invulnerable == 0)
    {
        for(int i = 0; i <= 5; i++)
        {
            if(player.spriteP.getGlobalBounds().intersects(enemies[i].shapeE.getGlobalBounds()))
            {
                player.setHealthPoints(player.getHealthPoints() - 1);
                player.spriteP.setPosition(sf::Vector2f(550,200));
                player.shapeP.setPosition(sf::Vector2f(550,200));
                updateHealth();
            }
        }

        for(int i = 0; i <= 4; i++)
        {
            if(player.spriteP.getGlobalBounds().intersects(pokeballs[i].shapeE2.getGlobalBounds()))
            {
                std::cout << "Spieler hittet Pokeball" << std::endl;
                player.setHealthPoints(player.getHealthPoints() -1);
                player.spriteP.setPosition(sf::Vector2f(550,200));
                player.shapeP.setPosition(sf::Vector2f(550,200));
                updateHealth();

            }
        }
        
    }
    for(int i = 0; i <= 2; i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].shapeC.getGlobalBounds()))
        {
            std::cout << "Collect" << std::endl;
            if(player.getCanCollect() == 1)
            {
                player.setCanCollect(0);                
            }
            collectables[i].spriteC.setPosition(2000,2000);
            collectables[i].shapeC.setPosition(2000,2000);
            collectables[i].collected = 1; // Variable für jedes Collectable, wenn true -> draw, wenn nicht -> nicht drawen
        }
    }

    if(player.spriteP.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
    {
        if(player.getCanCollect() == 0)
        {
            player.setCollected(player.getCollected() + 1);
            player.setCanCollect(1);
        }
    }
    player.invulnerable = 0; // vielleicht mit zeit versuchen?
    checkForWin();

}

void Field::checkForWin()
{
    if(player.getCollected() == 3)
    {
        std::cout << "Gewonnen" << std::endl;
    }
}

void Field::updateHealth()
{
    player.invulnerable = 1;
    for (int i = 0; i <= 2; i++)
    {
        if(i % 2 == 0)
        {
            player.shapeP.setFillColor(sf::Color::Red);
            field->draw(player.shapeP);
            field->display();
            Sleep(100);

        } else if(i % 2 != 0)
        {
            player.shapeP.setFillColor(sf::Color::Transparent);
            field->draw(player.shapeP);
            field->display();
            Sleep(100);
        }
    }

    if(player.getHealthPoints()== 2)
    {
        textureHP.loadFromFile("resources/health_bar_2.png");
        spriteHP.setTexture(textureHP);
    } else if(player.getHealthPoints() == 1)
    {
        textureHP.loadFromFile("resources/health_bar_1.png");
        spriteHP.setTexture(textureHP);
    } else if(player.getHealthPoints() == 0)
    {
        //Spiel verloren;
    }
    player.invulnerable = 0;
}

void Field::checkPositions()
{
    //PLAYER 
    for(int i = 0; i <= 2; i++)
    {
        if(player.shapeP.getGlobalBounds().intersects(collectables[i].shapeC.getGlobalBounds()))
        {
            std::cout << "Player bei Collectable" << std::endl;
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);
            newPosY = collectables[i].giveRandomNumber(0,1080);
            collectables[i].shapeC.setPosition(newPosX,newPosY);
            collectables[i].spriteC.setPosition(newPosX,newPosY);
            field->draw(collectables[i].spriteC);
        }
    }

    for(int i = 0; i <= 5; i++)
    {
        if(player.shapeP.getGlobalBounds().intersects(enemies[i].shapeE.getGlobalBounds()))
        {
            std::cout << "Player bei Enemy" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,1080);
            enemies[i].shapeE.setPosition(newPosX,newPosY);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            field->draw(enemies[i].spriteE);
        }
    }

    for(int i = 0; i <= 3; i++)
    {
        if(player.shapeP.getGlobalBounds().intersects(spriteTree[i].getGlobalBounds()))
        {
            std::cout << "Player bei Baum" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,1080);
            spriteTree[i].setPosition(newPosX,newPosY);
            field->draw(spriteTree[i]);
        }
    
    }

    //COLLECTABLES

    for(int i = 0; i <= 2; i++)
    {
        for(int k = 1; k <= 2; k++)
        {
            if(i + k > 2)
            {
                break;
            }
            if(collectables[i].shapeC.getGlobalBounds().intersects(collectables[i+k].shapeC.getGlobalBounds()))
            {
                std::cout << "Collectable ist bei anderem Collectable" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);
                newPosY = collectables[i].giveRandomNumber(0,1080);
                collectables[i].shapeC.setPosition(newPosX,newPosY);
                collectables[i].spriteC.setPosition(newPosX,newPosY);
                field->draw(collectables[i].spriteC);
            }
        }
    }

    for(int i = 0; i <= 5; i++)
    {
        for(int k = 0; k <= 2; k++)
        {
            if(enemies[i].shapeE.getGlobalBounds().intersects(collectables[i+k].shapeC.getGlobalBounds()))
            {
                std::cout << "Collectable bei Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,1080);
                enemies[i].shapeE.setPosition(newPosX,newPosY);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
            }
        }
    }

    for(int i = 0; i <= 3; i++)
    {
        for(int k = 0; k <= 2; k++)
        {
            if(spriteTree[i].getGlobalBounds().intersects(collectables[k].shapeC.getGlobalBounds()))
            {
                std::cout << "Collectable bei Baum" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[k].giveRandomNumber(0,1920);
                newPosY = collectables[k].giveRandomNumber(0,1080);
                collectables[k].shapeC.setPosition(newPosX,newPosY);
                collectables[k].spriteC.setPosition(newPosX,newPosY);
                field->draw(collectables[k].spriteC);
            }
        }
    }

    for(int i = 0; i <= 2; i++)
    {
        if(collectables[i].spriteC.getGlobalBounds().intersects(spritePD.getGlobalBounds()) || collectables[i].spriteC.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Collectable bei PC oder PD" << std::endl;
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);
            newPosY = collectables[i].giveRandomNumber(0,1080);
            collectables[i].shapeC.setPosition(newPosX,newPosY);
            collectables[i].spriteC.setPosition(newPosX,newPosY);
            field->draw(collectables[i].spriteC);
        }
    }

    //TREES

    for(int i = 0; i <= 3; i++)
    {
        for(int k = 1; k <= 3; k++)
        {
            if(i + k > 3)
            {
                break;
            }
            if(spriteTree[i].getGlobalBounds().intersects(spriteTree[i + k].getGlobalBounds()))
            {
                std::cout << "Baum ist bei anderem Baum" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);
                newPosY = collectables[i].giveRandomNumber(0,1080);
                spriteTree[i].setPosition(newPosX,newPosY);
                field->draw(spriteTree[i]);
            }
        }
    }
    
    for(int i = 0; i <= 3; i++)
    {
        for(int k = 0; k <= 5; k++)
        {
            if(spriteTree[i].getGlobalBounds().intersects(enemies[k].shapeE.getGlobalBounds()))
            {
                std::cout << "Tree ist bei Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[k].giveRandomNumber(0,1920);
                newPosY = enemies[k].giveRandomNumber(0,1080);
                spriteTree[i].setPosition(newPosX,newPosY);
                spriteTree[i].setPosition(newPosX,newPosY);
                field->draw(spriteTree[i]);
            }
        }
    }

    for(int i = 0; i <= 3; i++)
    {
        if(spriteTree[i].getGlobalBounds().intersects(spritePD.getGlobalBounds()) || spriteTree[i].getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Tree bei PC oder PD" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,1080);
            spriteTree[i].setPosition(newPosX,newPosY);
            spriteTree[i].setPosition(newPosX,newPosY);
            field->draw(spriteTree[i]);
        }
    }

    //ENEMIES

    for(int i = 0; i <= 5; i++)
    {
        for(int k = 1; k <= 5; k++)
        {
            if(i + k > 5)
            {
                break;
            }
            if(enemies[i].shapeE.getGlobalBounds().intersects(enemies[i+k].shapeE.getGlobalBounds()))
            {
                std::cout << "Enemy ist bei anderem Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,1080);
                enemies[i].shapeE.setPosition(newPosX,newPosY);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
            }
        }
    }

    for(int i = 0; i <= 5; i++)
    {
        if(enemies[i].shapeE.getGlobalBounds().intersects(spritePD.getGlobalBounds()) || enemies[i].shapeE.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Enemy und PC oder PD" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,1080);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            field->draw(enemies[i].spriteE);
        }
    }
    
    // Player mit allem kontrollieren Pokecenter mit allem kontrollieren Pokedex mit allem kontrollieren 
    //vielleicht mit structs?!

    field->display();

}


#include "field.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <chrono>           //include all necessary external files

/*----------------------------------------------------------------

    Letzte Änderungen:
    -> Tree Collision
    -> Sound
    -> Neue Pokeball Größe (in enemy2 nochmal schauen, ob da dann etwas geändert werden muss, soweit hat alles gepasst mit 58 und 263)
    
    TO-DO/BUGS
    -> Berg oben rechts als Grenze 
    -> Tree-Bug (Infos: an sich klappt die Kollision, wenn man dann aber zur Seite wechselt, schwebt man durch den Baum, wenn man von links oder unten gegenläuft: man bleibt stehen, wen von rechts oder oben: man wird verschoben)

    CODE-TECHNISCH:
    -> Field ist überladen, auslagern!
    -> Überprüfen, welche Funktionen wir wirklich benötigen
    -> main & game -> game useless?
    -> field.cpp: checkPositions verbessern
    -> KOMMENTARE! (gute Arbeit bis jetzt c: )
    -> checkCollison sehr überladen
    -> Gewinner/Verloren Screen sehr ähnlich vom Ablauf-> eigene funktion?

    PRÄSENTATION:
    -> Klassendiagramm (wenn alles fertig ist)
    -> probleme und wie mans gelöst hat (zufallsmethode, usw.)
    ->

*/

Field::Field()
{
    std::cout << "Field constructor" << std::endl;
    //SET VARIABLES - FIELD
    field = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pokemon-Hunt", sf::Style::Fullscreen);
    //field = new sf::RenderWindow(sf::VideoMode(1920,1080), "Pokemon-Hunt");
    field->setFramerateLimit(60);
    texturef.loadFromFile("resources/backgroundv3.png");
    texturef.setSmooth(true);
    spritef.setTexture(texturef);
    spritef.setOrigin(sf::Vector2f(texturef.getSize().x / 2,texturef.getSize().y / 2));
    spritef.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 2));
    //SET VARIABLES - SOUND
    bufferC.loadFromFile("resources/collected.wav");
    collected.setBuffer(bufferC);
    bufferW.loadFromFile("resources/win.wav");
    win.setBuffer(bufferW);
    bufferF.loadFromFile("resources/failure.wav");
    failure.setBuffer(bufferF);
    bufferD.loadFromFile("resources/damage.wav");
    damage.setBuffer(bufferD);
    //SET VARIABLES - HEALTH-BAR
    textureHP.loadFromFile("resources/health_bar_3.png");
    textureHP.setSmooth(true);
    spriteHP.setTexture(textureHP);
    spriteHP.setOrigin(sf::Vector2f(textureHP.getSize().x / 2,textureHP.getSize().y / 2));
    spriteHP.setPosition(1600,50);
    //SET VARIABLES - POKEDEX
    texturePD.loadFromFile("resources/collected_pokemon.png");
    texturePD.setSmooth(true);
    spritePD.setTexture(texturePD);
    spritePD.setOrigin(sf::Vector2f(texturePD.getSize().x / 2,texturePD.getSize().y / 2));
    spritePD.setPosition(250,1000);
    //SET VARIABLES - POKE CENTER
    texturePC.loadFromFile("resources/pokecenter.png");
    texturePC.setSmooth(true);
    spritePC.setTexture(texturePC);
    spritePC.setOrigin(sf::Vector2f(texturePC.getSize().x / 2,texturePC.getSize().y / 2));
    spritePC.setPosition(1800,500);
    //SET VARIABLES - TREES
    amountOfTrees = 4;
    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        if(i < amountOfTrees) {
            textureTree[i].loadFromFile("resources/tree.png");
            textureTree[i].setSmooth(true);
            spriteTree[i].setTexture(textureTree[i]);
            spriteTree[i].setOrigin(sf::Vector2f(textureTree[i].getSize().x / 2, textureTree[i].getSize().y / 2));
            spriteTree[i].setPosition(enemies[0].giveRandomNumber(0,1920), enemies[0].giveRandomNumber(0,900));
        } else if(i == (amountOfTrees-1) + 1) {
            textureTree[i].loadFromFile("resources/mountainTopRight.png");
            textureTree[i].setSmooth(true);
            spriteTree[i].setTexture(textureTree[i]);
            spriteTree[i].setPosition(texturef.getSize().x - textureTree[i].getSize().x, 0);
        } else if(i == (amountOfTrees-1) + 2) {
            textureTree[i].loadFromFile("resources/mountainTopLeft.png");
            textureTree[i].setSmooth(true);
            spriteTree[i].setTexture(textureTree[i]);
            spriteTree[i].setPosition(0, 0);
        }
    }   
    moves = 0;
    checkPositions();
}

Field::~Field()         //destructor
{
    std::cout << "Feld Dekonstruktor" << std::endl;
    delete field;
}

const bool Field::getFieldIsOpen() const
{
    return field->isOpen();                             
}

void Field::update()                                    //manages all the game data
{
    int movement, speed;                              //variable used for walking animation
    playerPosX = player.spriteP.getPosition().x;
    playerPosY = player.spriteP.getPosition().y;

    movement = playerPosY + playerPosX;                 //walking animation
    speed = player.getSpeed();

    
    //Close the window if wanted
    if(sf::Event::Closed)
    {
        field->close();

    }
    sf::Event event;
    //Check if any Key is pressed
    
    while(field->pollEvent(event));
    {

        if(InputDelayTimer.getElapsedTime() > InputDelay)
        {
            if((InputDelayTimer.getElapsedTime() > InputDelay) && ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::R)))))
            {
    

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    std::cout << moves << std::endl;
                    field->close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                {
                    resetGame();
                }
                //WASD_MOVEMENT
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    direction = 0;
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2) + ".png");
                    //movement++;       //wenn die Richtung nich geblockt is
                    playerPosY -= speed;
                    moves++;
                    
                    //direction = 0;              //setz momentane Richtung auf 0 / oben
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    direction = 1;
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 2) + ".png");
                    //movement++;
                    playerPosX -= speed;
                    moves++;
                    
                    //direction = 1;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    direction = 2;
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 4) + ".png");
                    //movement++;
                    playerPosY += speed;
                    moves++;
                    
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    direction = 3;
                    player.setTexture("resources/pikachu_" + std::to_string(movement % 2 + 6) + ".png");
                    //movement++;
                    playerPosX += speed;
                    moves++;
                }

                InputDelayTimer.restart();

            }
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
        if(playerPosY > 920 - (player.spriteP.getTexture()->getSize().y) / 2)
        {
            playerPosY = 920 - (player.spriteP.getTexture()->getSize().y) / 2;
        }

        player.spriteP.setPosition(playerPosX, playerPosY);
        player.shapeP.setPosition(playerPosX, playerPosY);
        //std::cout << "X: " + std::to_string(player.spriteP.getPosition().x) << std::endl;
        //std::cout << "Y: " + std::to_string(player.spriteP.getPosition().y) << std::endl;
    }
}

void Field::render() //displays the game data / game field
{
    field->clear();

    //DRAW OBJECTS
    field->draw(spritef);
    field->draw(spriteHP);
    field->draw(spritePD);
    field->draw(spritePC);
    
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        field->draw(enemies[i].spriteE);
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        field->draw(collectables[i].spriteC);
        
        if(!(collectables[i].spriteC.getGlobalBounds().intersects(spritePD.getGlobalBounds())))
        {
            positionCX[i] = collectables[i].spriteC.getPosition().x;
            positionCY[i] = collectables[i].spriteC.getPosition().y;
        }

    }

    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++)
    {
        field->draw(pokeballs[i].spriteE2);
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        field->draw(spriteTree[i]);
    }

    pokeballMovement();
    checkCollision();

    field->draw(player.spriteP);

    //DISPLAY NEW WINDOW
    field->display();
}

void Field::pokeballMovement()
{
    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++) {
        pokeballs[i].spriteE2.setPosition(((pokeballs[i].spriteE2.getPosition().x) - pokeballs[i].speed), pokeballs[i].spriteE2.getPosition().y);
        
        if(pokeballs[i].spriteE2.getPosition().x <= -100)
        {
            int newPosY;
            newPosY = pokeballs[i].giveRandomNumber(0,900);
            pokeballs[i].speed = pokeballs[i].fRand(7.5,9.5);
            pokeballs[i].spriteE2.setPosition(1970, newPosY);
        }
    }
}

void Field::checkCollision()
{
    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(enemies[i].spriteE.getGlobalBounds()))
        {
            player.setHealthPoints(player.getHealthPoints() - 1);
            player.spriteP.setPosition(sf::Vector2f(550,200));
            player.shapeP.setPosition(sf::Vector2f(550,200));
            updateHealth();
        }
    }

    for(int i = 0; i < (sizeof(pokeballs)/sizeof(pokeballs[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(pokeballs[i].spriteE2.getGlobalBounds()))
        {
            std::cout << "Spieler hittet Pokeball" << std::endl;
            player.setHealthPoints(player.getHealthPoints() -1);
            player.spriteP.setPosition(sf::Vector2f(550,200));
            player.shapeP.setPosition(sf::Vector2f(550,200));
            updateHealth();

        }
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].spriteC.getGlobalBounds()))
        {
            std::cout << "Collect" << std::endl;
            std::cout << player.getCollected() << std::endl;
            player.setCollected(player.getCollected() + 1);
            collectables[i].spriteC.setScale(0.5, 0.5);
            collected.play();
            //collected.setPlayingOffset(sf::seconds(200));
            //92 = spritePD.getPosition().x - spritePD.getTexture().x / 2 + 25
            //271 = spritePD.getPosition().x + spritePD.getTexture().x / 2 - 25 - collectable[0].getTexture().x - (spritePD.getPosition().x - spritePD.getTexture().x / 2 + 25)
            collectables[i].spriteC.setPosition(92 + (271/((sizeof(collectables)/sizeof(collectables[0]))-1) * (player.getCollected()-1)), 1000);
            //collectables[i].shapeC.setPosition(player.getCollected() * 110, 1000);
            //collectables[i].collected = 1; // Variable für jedes Collectable, wenn true -> draw, wenn nicht -> nicht drawen
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        while(player.spriteP.getGlobalBounds().intersects(spriteTree[i].getGlobalBounds()))
        {
            std::cout << "Tree " << std::to_string(direction) << std::endl;
            switch(direction){
                case 0:
                playerPosY++;
                break;
                case 1:
                playerPosX++;
                break;
                case 2:
                playerPosY--;
                break;
                case 3:
                playerPosX--;
                break;
            }
            player.spriteP.setPosition(playerPosX, playerPosY);
        }
    }

    if(player.spriteP.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
    {

        if (player.getCollected() >= 3) 
        {
            std::cout << "Gewonnen" << std::endl;

            field->clear();

            field->draw(spritef);
            field->draw(spritePC);
            for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
            {
                field->draw(spriteTree[i]);
            }

            textureSS.loadFromFile("resources/success_sprite.png");
            textureSS.setSmooth(true);
            spriteSS.setTexture(textureSS);
            spriteSS.setOrigin(sf::Vector2f(textureSS.getSize().x / 2, textureSS.getSize().y / 2));
            spriteSS.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 3));
            field->draw(spriteSS);

            textureSM.loadFromFile("resources/success_message.png");
            textureSM.setSmooth(true);
            spriteSM.setTexture(textureSM);
            spriteSM.setOrigin(sf::Vector2f(textureSM.getSize().x / 2, textureSM.getSize().y / 2));
            spriteSM.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 4 * 3));
            field->draw(spriteSM);

            score = (1150 - moves) / (4 - player.getHealthPoints());                //highest possible score: minimum of ~150 moves needed -> 1000
            if(score < 100) 
            {
                score = 100;
            }
            pokemonhollow.loadFromFile("resources/pokemon_hollow.ttf");
            scoretext.setFont(pokemonhollow);
            scoretext.setString("Score: " + std::to_string(score));
            scoretext.setCharacterSize(96);
            scoretext.setFillColor(sf::Color::Black);
            scoretext.setPosition(sf::Vector2f(100, field->getSize().y / 4));
            field->draw(scoretext);

            field->display();
            
            win.play();

            while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
            {   
                //std::cout << "waiting" << std::endl;
            }
            
            resetGame();
        }
    }

}

void Field::updateHealth()
{
    damage.play();
    for (int i = 0; i < 3; i++)
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
        field->clear();

        field->draw(spritef);
        field->draw(spritePC);
        for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
        {
            field->draw(spriteTree[i]);
        }


        textureHP.loadFromFile("resources/health_bar_0.png");
        spriteHP.setTexture(textureHP);
        field->draw(spriteHP);

        textureDS.loadFromFile("resources/death_sprite.png");
        textureDS.setSmooth(true);
        spriteDS.setTexture(textureDS);
        spriteDS.setOrigin(sf::Vector2f(textureDS.getSize().x / 2, textureDS.getSize().y / 2));
        spriteDS.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 3));
        field->draw(spriteDS);

        textureDM.loadFromFile("resources/death_message.png");
        textureDM.setSmooth(true);
        spriteDM.setTexture(textureDM);
        spriteDM.setOrigin(sf::Vector2f(textureDM.getSize().x / 2, textureDM.getSize().y / 2));
        spriteDM.setPosition(sf::Vector2f(field->getSize().x / 2, field->getSize().y / 4 * 3));
        field->draw(spriteDM);

        field->display();

        failure.play();

        while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
        {   
            //std::cout << "waiting" << std::endl;
        }
        
        resetGame();
    }
}

void Field::resetGame()
{
    player.setHealthPoints(3);
    player.setCollected(0);
    moves = 0;
    textureHP.loadFromFile("resources/health_bar_3.png");
    spriteHP.setTexture(textureHP);
    field->draw(spriteHP);
    playerPosX = 550;
    playerPosY = 200;
    field->draw(player.spriteP);
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(collectables[i].spriteC.getGlobalBounds().intersects(spritePD.getGlobalBounds()))
        {
            collectables[i].spriteC.setScale(1, 1);
        }
        collectables[i].spriteC.setPosition(positionCX[i], positionCY[i]);
    }
}

void Field::checkPositions()
{
    int done = 0;
    //PLAYER 
    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(collectables[i].spriteC.getGlobalBounds()))
        {
            std::cout << "Player bei Collectable" << std::endl;
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);
            newPosY = collectables[i].giveRandomNumber(0,900);
            collectables[i].spriteC.setPosition(newPosX,newPosY);
            field->draw(collectables[i].spriteC);
            done += 1;
        }
    }

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(enemies[i].spriteE.getGlobalBounds()))
        {
            std::cout << "Player bei Enemy" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            field->draw(enemies[i].spriteE);
            done += 1;
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        if(player.spriteP.getGlobalBounds().intersects(spriteTree[i].getGlobalBounds()))
        {
            std::cout << "Player bei Baum" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            spriteTree[i].setPosition(newPosX,newPosY);
            field->draw(spriteTree[i]);
            done += 1;
        }
    
    }

    //COLLECTABLES

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        for(int k = 1; k < (sizeof(collectables)/sizeof(collectables[0])); k++)
        {
            if(i + k > 2)
            {
                break;
            }
            if(collectables[i].spriteC.getGlobalBounds().intersects(collectables[i+k].spriteC.getGlobalBounds()))
            {
                std::cout << "Collectable ist bei anderem Collectable" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[i].giveRandomNumber(0,1920);
                newPosY = collectables[i].giveRandomNumber(0,900);
                collectables[i].spriteC.setPosition(newPosX,newPosY);
                field->draw(collectables[i].spriteC);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        for(int k = 0; k < (sizeof(collectables)/sizeof(collectables[0])); k++)
        {
            if(enemies[i].spriteE.getGlobalBounds().intersects(collectables[i+k].spriteC.getGlobalBounds()))
            {
                std::cout << "Collectable bei Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,900);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        for(int k = 0; k < (sizeof(collectables)/sizeof(collectables[0])); k++)
        {
            if(spriteTree[i].getGlobalBounds().intersects(collectables[k].spriteC.getGlobalBounds()))
            {
                std::cout << "Collectable bei Baum" << std::endl;
                int newPosX,newPosY;
                newPosX = collectables[k].giveRandomNumber(0,1920);
                newPosY = collectables[k].giveRandomNumber(0,900);
                collectables[k].spriteC.setPosition(newPosX,newPosY);
                field->draw(collectables[k].spriteC);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(collectables)/sizeof(collectables[0])); i++)
    {
        if(collectables[i].spriteC.getGlobalBounds().intersects(spritePD.getGlobalBounds()) || collectables[i].spriteC.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Collectable bei PC oder PD" << std::endl;
            int newPosX,newPosY;
            newPosX = collectables[i].giveRandomNumber(0,1920);
            newPosY = collectables[i].giveRandomNumber(0,900);
            collectables[i].spriteC.setPosition(newPosX,newPosY);
            field->draw(collectables[i].spriteC);
            done += 1;
        }
    }

    //TREES

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        for(int k = 1; k < (sizeof(spriteTree)/sizeof(spriteTree[0])); k++)
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
                newPosY = collectables[i].giveRandomNumber(0,900);
                spriteTree[i].setPosition(newPosX,newPosY);
                field->draw(spriteTree[i]);
                done += 1;
            }
        }
    }
    
    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        for(int k = 0; k < (sizeof(enemies)/sizeof(enemies[0])); k++)
        {
            if(spriteTree[i].getGlobalBounds().intersects(enemies[k].spriteE.getGlobalBounds()))
            {
                std::cout << "Tree ist bei Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[k].giveRandomNumber(0,1920);
                newPosY = enemies[k].giveRandomNumber(0,900);
                spriteTree[i].setPosition(newPosX,newPosY);
                spriteTree[i].setPosition(newPosX,newPosY);
                field->draw(spriteTree[i]);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(spriteTree)/sizeof(spriteTree[0])); i++)
    {
        if(spriteTree[i].getGlobalBounds().intersects(spritePD.getGlobalBounds()) || spriteTree[i].getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Tree bei PC oder PD" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            spriteTree[i].setPosition(newPosX,newPosY);
            spriteTree[i].setPosition(newPosX,newPosY);
            field->draw(spriteTree[i]);
            done += 1;
        }
    }

    //ENEMIES

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        for(int k = 1; k < (sizeof(enemies)/sizeof(enemies[0])); k++)
        {
            if(i + k > 5)
            {
                break;
            }
            if(enemies[i].spriteE.getGlobalBounds().intersects(enemies[i+k].spriteE.getGlobalBounds()))
            {
                std::cout << "Enemy ist bei anderem Enemy" << std::endl;
                int newPosX,newPosY;
                newPosX = enemies[i].giveRandomNumber(0,1920);
                newPosY = enemies[i].giveRandomNumber(0,900);
                enemies[i].spriteE.setPosition(newPosX,newPosY);
                field->draw(enemies[i].spriteE);
                done += 1;
            }
        }
    }

    for(int i = 0; i < (sizeof(enemies)/sizeof(enemies[0])); i++)
    {
        if(enemies[i].spriteE.getGlobalBounds().intersects(spritePD.getGlobalBounds()) || enemies[i].spriteE.getGlobalBounds().intersects(spritePC.getGlobalBounds()))
        {
            std::cout << "Enemy und PC oder PD" << std::endl;
            int newPosX,newPosY;
            newPosX = enemies[i].giveRandomNumber(0,1920);
            newPosY = enemies[i].giveRandomNumber(0,900);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            enemies[i].spriteE.setPosition(newPosX,newPosY);
            field->draw(enemies[i].spriteE);
            done += 1;
        }
    }
    
    if(done != 0)
    {
        printf("NeuerAufruf");
        checkPositions();
    }    
    
    // Player mit allem kontrollieren Pokecenter mit allem kontrollieren Pokedex mit allem kontrollieren 
    //vielleicht mit structs?!

    field->display();

}


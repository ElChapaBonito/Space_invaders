//
// Created by anast on 01/11/2024.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "world.h"
#include "../include/ResourceHolder.h"

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

class Game {
public:
                        Game();
    void                run();



private:
    sf::RenderWindow                                            myWindow;
    ResourceHolder<Texture::ID, sf::Texture>                    myTextureHolder;
    World                                                       myWorld;
    Player                                                      myPlayer;

private:
    void                processInputs();
    void                update(sf::Time dt);
    void                render();
};


#endif //GAME_H

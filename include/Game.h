//
// Created by anast on 01/11/2024.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "State.h"
#include "Player.h"
#include "world.h"
#include "ResourceHolder.h"



class Game: public State {
public:
                        Game(StateStack& stack, Context context);
                        ~Game(){};


private:
    sf::RenderWindow&                                            myWindow;
    Player&                                                      myPlayer;
    World                                                        myWorld;
    

private:
    bool                handleEvent(const sf::Event& event) override;
    bool                update(sf::Time dt) override;
    void                draw() override;
};


#endif //GAME_H

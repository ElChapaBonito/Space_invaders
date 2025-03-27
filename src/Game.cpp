//
// Created by anast on 01/11/2024.
//


#include "../include/Game.h"


void fpsCounter(sf::Clock& clock, float& fps_count);


//Public methods

Game::Game()
:myWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Space Invaders")
,myWorld(myWindow){}


void Game::run() {
    sf::Clock CycleClock,
              FPSClock;
    sf::Time dt;
    float fpsCount = 0;

    while(myWindow.isOpen()) {
        dt = CycleClock.restart();
        processInputs();
        update(dt);
        fpsCounter(FPSClock, fpsCount);
        render();
    }
}


//Private methods


void Game::processInputs() {

    sf::Event evento;
    CommandQueue& commands = myWorld.getCommandQueue();


    while (myWindow.pollEvent(evento)) {

        if (evento.type == sf::Event::Closed) {
            myWindow.close();
        }

        myPlayer.handleEvent(evento, commands);

    }

    myPlayer.handleRealtimeInput(commands);
}


void Game::update(sf::Time dt) {
    myWorld.update(dt);
}

void Game::render() {
    myWindow.clear();
    myWorld.draw();
    myWindow.display();
}

void fpsCounter(sf::Clock& clock, float& fps_count) {

    auto elapseTime = clock.getElapsedTime().asSeconds();
    if(elapseTime > 1) {
        std::cout << "FPS: " << fps_count / elapseTime << std::endl;
        fps_count = 0;
        clock.restart();
    }
    fps_count++;
}


//
// Created by anast on 01/11/2024.
//


#include "../include/Game.h"


void fpsCounter(sf::Clock& clock, float& fps_count);


//Public methods

Game::Game(StateStack& stack, Context context):
    myPlayer(*context.player),
    myWorld(*context.window),
    State(stack, context),
    myTextureHolder(*context.textures),
    myWindow(*context.window)
    {}


void Game::run() {
    /*sf::Clock CycleClock,
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

*/
}


//Private methods


bool Game::handleEvent(const sf::Event& event) {

    CommandQueue& commands = myWorld.getCommandQueue();

    myPlayer.handleEvent(event, commands);

    myPlayer.handleRealtimeInput(commands);
}


bool Game::update(sf::Time dt) {
    myWorld.update(dt);
    return true;
}

void Game::draw() {
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


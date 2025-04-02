//
// Created by anast on 01/11/2024.
//


#include "../include/Game.h"


void fpsCounter(sf::Clock& clock, float& fps_count);


//Public methods

Game::Game(StateStack& stack, Context context):
    
    State(stack, context),
    myWindow(*context.window),
    myPlayer(*context.player),
    myWorld(*context.window){
        
}

//Private methods


bool Game::handleEvent(const sf::Event& event) {
    
    CommandQueue& commands = myWorld.getCommandQueue();

    myPlayer.handleEvent(event, commands);

    myPlayer.handleRealtimeInput(commands);
    
    return true;
}


bool Game::update(sf::Time dt) {
    myWorld.update(dt);
    return true;
}

void Game::draw() {
    myWorld.draw();
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


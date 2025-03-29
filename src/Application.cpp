#include "Application.h"
#include "Game.h"
#include <iostream>

Application::Application(): 
mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space invaders"),
mStateStack({&mTextureHolder, &mWindow, &mFontsHolder, &mPlayer})
{
    registerStates();
    mStateStack.pushState(State::ID::GAME);
};

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.f/60.f); // 60 FPS

    while (mWindow.isOpen())
    {
        processInputs();
        timeSinceLastUpdate += clock.restart();
        
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processInputs();
            update(timePerFrame);
        }

        mWindow.clear();
        draw();
        mWindow.display();
    }
}

void Application::processInputs() 
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {  // Changed from !mWindow.pollEvent
        mStateStack.processEvents(event);
    }
}

void Application::update(sf::Time dt) {

    mStateStack.update(dt);

};

void Application::draw(){

    mStateStack.draw();
}

void Application::registerStates() {
    mStateStack.RegisterState<Game>(State::ID::GAME);
    //mStateStack.RegisterState<Pause>(State::ID::PAUSE);
    //mStateStack.RegisterState<MainMenu>(State::ID::MAIN_MENU);
}

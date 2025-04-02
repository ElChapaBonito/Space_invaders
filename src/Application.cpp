#include "Application.h"
#include "Game.h"
#include <iostream>

Application::Application(): 


mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space invaders"),
mPlayer(),
mTextureHolder(),
mFontsHolder(),

mStateStack({&mTextureHolder, &mWindow, &mFontsHolder, &mPlayer})

{
    registerStates();
    mStateStack.pushState(State::ID::GAME);
};

void Application::run()
{
    const sf::Time timePerFrame = sf::seconds(1.f / 30.f); // 60 FPS
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;

            // Process inputs
            processInputs();

            // Update game logic
            update(timePerFrame);
        }

        // Render the frame
        draw();
    }
}

void Application::processInputs() 
{
    
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if(event.type==sf::Event::Closed)
            mWindow.close();  // Changed from !mWindow.pollEvent
        mStateStack.processEvents(event);
    }
}

void Application::update(sf::Time dt) {

    mStateStack.update(dt);

};

void Application::draw(){
    mWindow.clear();
    mStateStack.draw();
    mWindow.display();
}

void Application::registerStates() {
    mStateStack.RegisterState<Game>(State::ID::GAME);
    //mStateStack.RegisterState<Pause>(State::ID::PAUSE);
    //mStateStack.RegisterState<MainMenu>(State::ID::MAIN_MENU);
}

#ifndef APPLICATION_H
#define APPLICATION_H

#include "State.h"
#include "Player.h"
#include "ResourceHolder.h"

#include "Game.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>


constexpr unsigned int SCREEN_WIDTH = 1920;
constexpr unsigned int SCREEN_HEIGHT = 1080;



class Application {

    public:
                                                Application();
    void                                        run();


    private:
    void                                        processInputs();
    void                                        update(sf::Time dt);
    void                                        draw();
    void                                        registerStates();

    private:
    StateStack                                  mStateStack;

    sf::RenderWindow                            mWindow;
    Player                                      mPlayer;
    TextureHolder                               mTextureHolder;
    FontHolder                                  mFontsHolder;
};




#endif
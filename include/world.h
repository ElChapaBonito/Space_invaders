//
// Created by anast on 24/11/2024.
//

#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include "ResourceHolder.h"
#include "Aircraft.h"
#include "Command.h"
#include "State.h"

const int BackGroundLenght = 100000;

class World {
public:
    typedef  ResourceHolder<Texture::ID, sf::Texture> TextureHolder;

    explicit                            World(sf::RenderWindow& window);
    void                                update(sf::Time dt);
    void                                draw();
    CommandQueue&                       getCommandQueue();


private:
enum Layer {
    Background,
    Air,
    LayerCount
};
private:
    void                                loadTexture();
    void                                buildScene();
private:
    sf::RenderWindow&                    mWindow;
    sf::View                             mView;
    TextureHolder                        mTextureHolder;
    SceneNode                            mSceneGraph;
    std::array<SceneNode*, LayerCount>   mSceneLayers;

    Aircraft*                            mPlayerAircraft;
    sf::Vector2f                         mSpawnPosition;
    float                                mScrollSpeed;
    sf::FloatRect                        mWorldBounds;
    CommandQueue                         mCommandQueue;
};



#endif //WORLD_H

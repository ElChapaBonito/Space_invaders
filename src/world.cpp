//
// Created by anast on 24/11/2024.
//
#include "../include/world.h"

#include <cmath>
#include <iostream>

#include "../include/SpriteNode.h"

class SpriteNode;
class CommandQueue;

World::World(sf::RenderWindow& window)
    : mWindow(window)
      , mView(window.getDefaultView())
      ,mWorldBounds(
          0,
          0,
          mView.getSize().x,
          BackGroundLenght)
      ,mPlayerAircraft(nullptr)
      ,mScrollSpeed(-100)

{
    mSpawnPosition =sf::Vector2f(mView.getSize().x / 2.0f, mWorldBounds.height - mView.getSize().y/ 2.0) ;
    loadTexture();
    buildScene();
    mView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt) {
    mView.move(0, mScrollSpeed * dt.asSeconds());

    sf::Vector2f position = mPlayerAircraft->getPosition();
    mPlayerAircraft->setVelocity(0,0);


    while(!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(),dt);

    sf::Vector2f velocity = mPlayerAircraft->getVelocity();
    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
    mPlayerAircraft->acellerate(sf::Vector2f(0.f, mScrollSpeed));

    sf::Vector2f pos = mPlayerAircraft->getPosition();
    sf::FloatRect viewLimits(mView.getCenter()-mView.getSize()/2.0f, mView.getSize());
    pos.x = std::max<float>(pos.x, viewLimits.left);
    pos.x = std::min<float>(pos.x, viewLimits.left + viewLimits.width);
    pos.y = std::max<float>(pos.y, viewLimits.top);
    pos.y = std::min<float>(pos.y, viewLimits.top + viewLimits.height);
    mPlayerAircraft->setPosition(pos);

    mSceneGraph.update(dt);
}

void World::draw() {
    mWindow.setView(mView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

void World::loadTexture() {
    mTextureHolder.load(Texture::ID::F22, "./res/F22.png");
    mTextureHolder.load(Texture::ID::Typhoon, "./res/Typhoon.png");
    mTextureHolder.load(Texture::ID::Sfondo, "./res/Sfondo.jpg");
}

void World::buildScene() {

    for(std::size_t i = 0; i<LayerCount; i++) {
        SceneNode::Ptr layer(new SceneNode());

        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = mTextureHolder.get(Texture::ID::Sfondo);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> BackGroundSprite(new SpriteNode(texture, textureRect));
    BackGroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);

    mSceneLayers[Layer::Background] -> attachChild(std::move(BackGroundSprite));


    std::unique_ptr<Aircraft> leader(std::make_unique<Aircraft>(Aircraft::Type::F22, mTextureHolder));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(200.f,mScrollSpeed);
    mSceneLayers[Layer::Air] -> attachChild(std::move(leader));
}

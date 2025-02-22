//
// Created by anast on 24/11/2024.
//

#include "../include/Entity.h"

Entity::Entity():SceneNode() {
}

void Entity::setVelocity(float vx, float vy) {
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Entity::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

sf::Vector2f Entity::getVelocity() {
    return mVelocity;
}

void Entity::updateCurrent(sf::Time dt) {
    setPosition(getPosition() + mVelocity * dt.asSeconds());
}

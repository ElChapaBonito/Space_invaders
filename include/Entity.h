//
// Created by anast on 24/11/2024.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "SceneNode.h"

class Entity: public SceneNode {
    public:
                            Entity();
    void                    setVelocity(float vx, float vy);
    void                    setVelocity(sf::Vector2f velocity);
    sf::Vector2f            getVelocity();
    virtual void            updateCurrent(sf::Time dt) override;

    private:
    sf::Vector2f             mVelocity;
};



#endif

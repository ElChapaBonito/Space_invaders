//
// Created by anast on 24/11/2024.
//

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "ResourceHolder.h"
#include "SceneNode.h"
#include"../include/ResourceHolder.h"

typedef  ResourceHolder<Texture::ID, sf::Texture> TextureHolder;

class Aircraft: public Entity {
public:
    enum Type {
        F22,
        Typhoon
    };

public:
    Aircraft(Type type);
    explicit                    Aircraft(Type type, const TextureHolder& textures);
    virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void                        acellerate(sf::Vector2f velocity);

private:
    sf::Sprite          mSprite;
    Type                mType;

};




#endif //AIRCRAFT_H

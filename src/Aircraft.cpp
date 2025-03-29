//
// Created by anast on 24/11/2024.
//

#include "Aircraft.h"
#include <SFML/Graphics/RenderTarget.hpp>


Texture::ID toTextureID(Aircraft::Type type) {
    switch (type) {
        case Aircraft::Type::F22:
            return Texture::ID::F22;
        case Aircraft::Type::Typhoon:
            return Texture::ID::Typhoon;
        default:
            return Texture::ID::None;
    }
}



Aircraft::Aircraft(Type type):mType(type) {
    this->setCategory(Category::Type::PlayerAircraft);
}



Aircraft::Aircraft(Type type, const TextureHolder& textures)
:mType(type)
,mSprite(textures.get(toTextureID(type))){
    this->setCategory(Category::Type::PlayerAircraft);
    sf::FloatRect bounds =  mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2, bounds.height / 2);
}



void Aircraft::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite,states);
}

void Aircraft::acellerate(sf::Vector2f velocity) {
    this->setVelocity(this->getVelocity() + velocity);
}


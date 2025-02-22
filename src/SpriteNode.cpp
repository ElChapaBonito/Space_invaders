//
// Created by anast on 24/11/2024.
//
#include "../include/SpriteNode.h"

#include <SFML/Graphics/RenderTarget.hpp>


SpriteNode::SpriteNode(sf::Texture &texture)
:mSprite(texture) {
}



SpriteNode::SpriteNode(sf::Texture &texture, sf::IntRect &textureRect)
:mSprite(texture, textureRect) {
}


void SpriteNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

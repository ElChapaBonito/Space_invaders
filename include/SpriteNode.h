//
// Created by anast on 24/11/2024.
//

#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <stdexcept>
#include <SFML/Graphics/Sprite.hpp>

#include "SceneNode.h"

class SpriteNode: public SceneNode {
public:
    explicit                                SpriteNode(sf::Texture& texture);
                                            SpriteNode(sf::Texture& texture, sf::IntRect& textureRect);

private:
    virtual void                            draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Sprite                              mSprite;
};



#endif //SPRITENODE_H

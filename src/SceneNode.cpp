//
// Created by anast on 24/11/2024.
//

#include "../include/SceneNode.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include "../include/Command.h"

Category::Type SceneNode::getCategory() const {
    return mCategory;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states)const {

    states.transform *= getTransform();

    drawCurrent(target, states);

    for(const auto& child: mChildren) {
        child->draw(target,states);
    }

}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states)const {
}


void SceneNode::attachChild(Ptr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {

    auto found = std::find_if(mChildren.begin(), mChildren.end(),
        [&] (Ptr& p) -> bool {return p.get()== &node;});
    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

SceneNode::SceneNode():mParent(nullptr), mCategory(Category::Type::Scene) {
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt) {
}

void SceneNode::updateChildren(sf::Time dt) {
    for(auto& child: mChildren) {
        child->update(dt);
    }
}

void SceneNode::onCommand(const Command &cmd, sf::Time dt) {
    if(cmd.category & getCategory())
        cmd.action(*this, dt);
    for(auto& child: mChildren)
        child->onCommand(cmd, dt);

}

void SceneNode::setCategory(const Category::Type category) {
    mCategory = category;
}

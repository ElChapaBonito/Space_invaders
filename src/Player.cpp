//
// Created by anast on 25/11/2024.
//


#include "../include/Player.h"
#include <cassert>
#include "../include/Aircraft.h"
#include <iostream>

class Aircraft;

template<typename ObjectType, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
    return [=] (SceneNode& node, sf::Time dt)->void {

        assert(dynamic_cast<ObjectType*>(&node) != nullptr);

        fn(static_cast<ObjectType&> (node), dt);
    };
}


struct aircraftMover {
    aircraftMover(float vx, float vy): velocity(vx, vy){};
    void operator() (Aircraft &aircraft, sf::Time dt) const {
        aircraft.acellerate(velocity);
    }
    sf::Vector2f velocity;
};



void Player::handleRealtimeInput(CommandQueue &commands) {


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        Command moveUp;
        moveUp.category = Category::Type::PlayerAircraft;
        moveUp.action = derivedAction<Aircraft>(aircraftMover(0, -playerSpeed));
        commands.push(moveUp);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Command moveLeft;
        moveLeft.category = Category::Type::PlayerAircraft;
        moveLeft.action = derivedAction<Aircraft>(aircraftMover(-playerSpeed, 0));
        commands.push(moveLeft);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Command moveDown;
        moveDown.category = Category::Type::PlayerAircraft;
        moveDown.action = derivedAction<Aircraft>(aircraftMover(0, playerSpeed));
        commands.push(moveDown);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Command moveRight;
        moveRight.category = Category::Type::PlayerAircraft;
        moveRight.action = derivedAction<Aircraft>(aircraftMover(playerSpeed, 0));
        commands.push(moveRight);
    }

}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {

}

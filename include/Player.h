//
// Created by anast on 25/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Event.hpp>

#include "Command.h"

class Player {
public:
    void                                     handleEvent(const sf::Event& event, CommandQueue& commands);
    void                                     handleRealtimeInput(CommandQueue& commands);
};



#endif //PLAYER_H

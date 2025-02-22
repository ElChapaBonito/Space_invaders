//
// Created by anast on 25/11/2024.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <functional>
#include <queue>
#include <SFML/System/Time.hpp>
#include "../include/SceneNode.h"

struct Command {

    std::function<void(SceneNode&, sf::Time)>                   action;
    unsigned int                                                category;

};

class CommandQueue {

public:
    void                    push(const Command& command);
    Command                 pop();
    bool                    isEmpty() const;

private:
    std::queue<Command> mQueue;
};


#endif //COMMAND_H

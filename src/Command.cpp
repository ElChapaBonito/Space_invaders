//
// Created by anast on 25/11/2024.
//


#include "../include/Command.h"


void CommandQueue::push(const Command &command) {
    mQueue.push(command);

}

Command CommandQueue::pop() {
    auto result = mQueue.front();
    mQueue.pop();
    return result;
}

bool CommandQueue::isEmpty() const {
    return mQueue.empty();
}

#include "State.h"
#include <cassert>
#include <iostream>

StateStack::StateStack(State::Context context): mContext(context)
{
}

void StateStack::processEvents(const sf::Event &event)
{
    
    for(auto r_it = mStack.rbegin(); r_it != mStack.rend(); r_it++){
        if(!((*r_it)->handleEvent(event)))
            break;
    }

    //applyPendingChanges(); // Perche sta roba sta qui?
}

void StateStack::update(sf::Time dt)
{
    for(auto r_it = mStack.rbegin(); r_it != mStack.rend(); r_it++){
        if(!(*r_it)->update(dt)){
            return;
        }
    }
}

void StateStack::draw()
{
    for(auto r_it = mStack.rbegin(); r_it != mStack.rend(); r_it++){
        (*r_it)->draw();
    }
}

void StateStack::pushState(State::ID id)
{

    auto it = mFactories.find(id);
    
    assert(it != mFactories.end());

    mStack.push_back(std::move(it->second()));
}

void StateStack::popState() {
    mStack.pop_back();
};


void StateStack::clearStates(){
    mStack.clear();
}


State::Ptr StateStack::createState(State::ID id){

    auto it = mFactories.find(id);

    assert(it != mFactories.end());

    return it->second();
}

void StateStack::applyPendingChanges() {

    for(auto& currChange: mPendingChanges){
        switch(currChange.action){
            case Action::Clear:
                clearStates();
                break;
            case Action::Pop:
                popState();
                break;
            case Action::Push:
                pushState(currChange.id);
                break;
        }
    }

    mPendingChanges.clear();
    
}
/*
template<typename T>
void StateStack::RegisterState(State::ID id) {
    mFactories[id] = [this] () {
    
        return std::make_unique<T>(*this, this->mContext);
    
    };
}
*/
State::State(StateStack &stack, Context context):mStack(&stack), mContext(context)
{
}

void State::requestStatePush(State::ID id)
{
}
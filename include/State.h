#ifndef STATE_H
#define STATE_H




#include "ResourceHolder.h"
#include "Player.h"

#include <map>
#include <memory>
#include <functional>
#include <stack>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class StateStack;

class State {

    public:

    enum class ID {
        MAIN_MENU,
        GAME,
        PAUSE
    };

    struct Context {
        Context(TextureHolder* tex, sf::RenderWindow* win, FontHolder* fon, Player* pla):
        textures(tex), window(win), fonts(fon), player(pla){};

        TextureHolder*                  textures;
        sf::RenderWindow*               window;
        FontHolder*                     fonts;
        Player*                         player;
    
    };

    using FactoryType = std::function<std::unique_ptr<State>()>;
    using Ptr = std::unique_ptr<State>;
    public:
                                        State(StateStack& stack, Context context);
    virtual                             ~State() = default;

    virtual void                        draw()=0;
    virtual bool                        update(sf::Time dt)=0;
    virtual bool                        handleEvent(const sf::Event& event)=0;

    protected:
    void                                requestStatePush(State::ID id);
    void                                requestStatePop();

    Context                             getContext();

    private:
    StateStack*                         mStack;
    Context                             mContext;
};


class StateStack: private sf::NonCopyable {

    public:
    enum Action {
        Pop,
        Push,
        Clear,
    };

    public:
    explicit                                    StateStack(State::Context context);
    
    template<typename T>
    void                                        RegisterState(State::ID id){
        mFactories[id] = [this] () {
        return std::make_unique<T>(*this, this->mContext);
        
        };
    }
    std::size_t                                 size()const{return mStack.size();} ;
    void                                        processEvents(const sf::Event& event);
    void                                        update(sf::Time dt);
    void                                        draw();

    void                                        pushState(State::ID id);
    void                                        popState();
    void                                        clearStates();

    private:
    State::Ptr                                  createState(State::ID id);
    void                                        applyPendingChanges();


    private:
    struct PendingChange {
        Action                                      action;
        State::ID                                   id;
    };


    private:
    std::map<State::ID, State::FactoryType>                         mFactories;
    State::Context                                                  mContext;
    std::vector<std::unique_ptr<State>>                             mStack;
    std::vector<PendingChange>                                      mPendingChanges;

};








#endif
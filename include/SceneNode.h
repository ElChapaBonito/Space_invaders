//
// Created by anast on 24/11/2024.
//

#ifndef CLASSESANDDS_H
#define CLASSESANDDS_H
#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/ThreadLocal.hpp>
#include <SFML/System/Time.hpp>

class Command;
class CommandQueue;

namespace Category {
    enum Type {
        None            = 0,
        Scene           = 1 << 1,
        PlayerAircraft  = 1 << 2
    };
}

class SceneNode: public sf::Transformable, public sf::Drawable, private sf::NonCopyable{

public:
    typedef std::unique_ptr<SceneNode> Ptr;

    SceneNode();
    void                            attachChild(Ptr child);
    Ptr                             detachChild(const SceneNode& node);
    void                            update(sf::Time dt);
    virtual void                    updateCurrent(sf::Time dt);
    virtual void                    updateChildren(sf::Time dt);
    void                            onCommand(const Command& cmd, sf::Time dt);
    void                            setCategory(const Category::Type category);
private:
    SceneNode* mParent;
    std::vector<Ptr> mChildren;
    Category::Type mCategory;
private:
    virtual Category::Type                  getCategory() const;
    virtual void                            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void                            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif //CLASSESANDDS_H

//
// Created by anast on 01/11/2024.
//

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H
#include <memory>
#include<cassert>

namespace Texture {
    enum ID {F22, Typhoon, Sfondo,None};
};

template<typename Identifier, typename Resource>
class ResourceHolder {
    public:
    void                load(Identifier identifier, const std::string& filename);
    Resource&           get(Identifier identifier);
    const Resource&     get(Identifier identifier) const;

    private:
    std::map<Identifier, std::unique_ptr<Resource>> myResources;
};


template<typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::load(Identifier identifier, const std::string& filename) {

    std::unique_ptr<Resource> resource(new Resource());

    if(!resource->loadFromFile(filename))
        throw std::runtime_error("Failed to load resource from file " + filename);

    auto inserted = myResources.insert(std::make_pair(identifier, std::move(resource)));
    assert(inserted.second);
}


template<typename Identifier, typename Resource>
Resource &ResourceHolder<Identifier, Resource>::get(Identifier identifier) {
    return *myResources.at(identifier);
}


template<typename Identifier, typename Resource>
const Resource &ResourceHolder<Identifier, Resource>::get(Identifier identifier) const {
    return *myResources.at(identifier);
}


#endif //RESOURCEHOLDER_H

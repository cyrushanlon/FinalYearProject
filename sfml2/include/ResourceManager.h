#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include"Resource.h"

#include<map>
#include<SFML/Graphics.hpp>

//holds all loaded resources to allow for reuse
class ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();

    sf::Texture Load(std::string);

protected:

private:
    std::map<std::string, Resource> textures;
};

#endif // RESOURCEMANAGER_H

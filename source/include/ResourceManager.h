#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include"Resource.h"

#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

//holds all loaded resources to allow for reuse
class ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();

    sf::Texture LoadTexture(std::string);
/*
    template<class T>
    T Load(std::string uri)
    {
        //we need to load the resource from disk
        if (this->resources.count(uri) != 1)
        {
            //we need to read from file and insert it into the map
            T resource;
            resource.loadFromFile(uri);

            Resource<T> newResource;
            newResource.resource = resource;
            newResource.Useage = 0;

            resources.insert({uri, &newResource});
            std::cout << "[ResourceManager] Loaded  |\"" << uri <<"\"" <<std::endl;
        }

        resources[uri]->Useage++;
        Resource<T> rsc = *static_cast<Resource<T> *>(resources[uri]);

        return rsc.resource;
    }
*/
    void Unload(std::string);

protected:

private:
    std::map<std::string, Resource<sf::Texture>> textures;
    //std::map<std::string, Resource<sf::SoundBuffer>> sounds;
};

#endif // RESOURCEMANAGER_H

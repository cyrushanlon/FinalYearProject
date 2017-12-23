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
    void Unload(std::string);

    std::shared_ptr<sf::Image> LoadImage(std::string);
    std::shared_ptr<sf::Texture> LoadTexture(std::string);
    std::shared_ptr<sf::SoundBuffer> LoadSoundBuffer(std::string);

protected:

private:
    std::map<std::string, ResourceInterface*> resources;

    //templated functions cant be declared in another file
    //generic load from map function
    template<class T>
    std::shared_ptr<T> load(std::string uri)
    {
        if (this->resources.count(uri) != 1)
        {
            std::shared_ptr<T> rsc = std::shared_ptr<T>(new T);
            rsc.get()->loadFromFile(uri);

            Resource<T>* newResource = new Resource<T>(rsc, 0);

            resources.insert({uri, newResource});
            std::cout << "[ResourceManager] Loaded  |\"" << uri <<"\"" <<std::endl;
        }

        resources[uri]->Useage++;
        auto rsc = resources[uri];

        return dynamic_cast<Resource<T>*>(rsc)->resource;
    }

};

#endif // RESOURCEMANAGER_H

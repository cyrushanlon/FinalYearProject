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

    bool Exists(std::string);

    //generic add to map function
    //add texture not from file but from a variable
    template<class T>
    void Add(T resource, std::string uri)
    {
        if (this->resources.count(uri) != 1)
        {
            std::shared_ptr<T> rsc = std::make_shared<T>(resource);
            Resource<T>* newResource = new Resource<T>(rsc, 0);

            resources.insert({uri, newResource});
            std::cout << "[ResourceManager] Added  |\"" << uri <<"\"" <<std::endl;
        }
        else //already exists so we overwrite it(?)
        {
            //std::cout << "[ResourceManager] Overwritten  |\"" << uri <<"\"" <<std::endl;
        }

    }

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

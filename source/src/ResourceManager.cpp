#include "ResourceManager.h"
#include<iostream>

ResourceManager::ResourceManager()
{
    //ctor
}

ResourceManager::~ResourceManager()
{
    //dtor
}

std::shared_ptr<sf::Texture> ResourceManager::LoadTexture(std::string uri)
{
    if (this->textures.count(uri) != 1)
    {
        auto tex = std::shared_ptr<sf::Texture>(new sf::Texture);
        tex.get()->loadFromFile(uri);

        //transparency mask on magenta
        sf::Image img = tex.get()->copyToImage();
        img.createMaskFromColor(sf::Color::Magenta);
        tex.get()->loadFromImage(img);

        Resource<sf::Texture> newResource;
        newResource.resource = tex;
        newResource.Useage = 0;

        textures.insert({uri, newResource});
        std::cout << "[ResourceManager] Loaded  |\"" << uri <<"\"" <<std::endl;
    }

    textures[uri].Useage++;
    auto rsc = textures[uri];
    //std::unique_ptr<Resource<sf::Texture>> rsc = dynamic_cast<std::unique_ptr<Resource<sf::Texture>>>(resources[uri]);

    return rsc.resource;
}

/*
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

void ResourceManager::Unload(std::string uri)
{
    //if the resource actually exists
    if (this->textures.count(uri) == 1)
    {
        int curCount = textures[uri].Useage--;

        if (curCount <= 1) //use 1 here as the decrement happens after the assignment so when val is 1 actual val is 0
        {
            this->textures.erase(uri);
            std::cout << "[ResourceManager] Removed |\"" << uri <<"\""<<std::endl;
        }
    }
}

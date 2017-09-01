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

sf::Texture ResourceManager::Load(std::string uri)
{
    //we need to load the resource from disk
    if (this->textures.count(uri) != 1)
    {
        //we need to read from file and insert it into the map
        sf::Texture texture;
        texture.loadFromFile(uri); //maybe we want the path to be added here so the user doesnt have to bother

        //transparency mask on magenta
        auto img = texture.copyToImage();
        img.createMaskFromColor(sf::Color::Magenta);
        texture.loadFromImage(img);

        Resource newResource;
        newResource.Texture = texture;
        newResource.Useage = 0;

        textures.insert({uri, newResource});
        std::cout << "[ResourceManager] Loaded  |\"" << uri <<"\"" <<std::endl;
    }

    textures[uri].Useage++;
    return textures[uri].Texture;
}

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

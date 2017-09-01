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
    }

    textures[uri].Useage++;
    std::cout<<textures[uri].Useage;
    return textures[uri].Texture;
}

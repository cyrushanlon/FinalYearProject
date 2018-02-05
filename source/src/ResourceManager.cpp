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

std::shared_ptr<sf::Image> ResourceManager::LoadImage(std::string uri)
{
    auto rsc = this->load<sf::Image>(uri);

    return rsc;
}

std::shared_ptr<sf::Texture> ResourceManager::LoadTexture(std::string uri)
{
    auto rsc = this->load<sf::Texture>(uri);

    //transparency mask on magenta
    sf::Image img = rsc.get()->copyToImage();
    img.createMaskFromColor(sf::Color::Magenta);
    rsc.get()->loadFromImage(img);

    return rsc;
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::LoadSoundBuffer(std::string uri)
{
    auto rsc = this->load<sf::SoundBuffer>(uri);

    return rsc;
}

bool ResourceManager::Exists(std::string uri)
{
    return this->resources.count(uri);
}

void ResourceManager::Unload(std::string uri)
{
    //if the resource actually exists
    if (this->resources.count(uri) == 1)
    {
        //std::cout << "UNLOADING: " << uri << " USES: " << resources[uri]->Usage() << std::endl;
        int curCount = resources[uri]->Usage() - 1; //-1 as the current one needs to be removed

        if (curCount == 1) //the single use should be the one in the manager
        {
            //this->resources.erase(uri);
            std::cout << "[ResourceManager] Removed |\"" << uri <<"\""<<std::endl;
        }
    }
}

#include "ECSManager.h"

ECSManager::ECSManager()
{
    //ctor
}

ECSManager::~ECSManager()
{
    //dtor
}

void ECSManager::Draw(sf::RenderWindow& window)
{
    this->drawables.Draw(window);
    this->text.Draw(window);
}

void ECSManager::Think(sf::Time dt)
{
    //this->animatables.Think(dt);
    this->physics.Think(dt);
    this->drawables.Think(dt);
}

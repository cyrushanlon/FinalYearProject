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
    drawableSystem.Draw(window);
}

void ECSManager::Think(sf::Time dt)
{

}

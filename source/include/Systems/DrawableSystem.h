#ifndef DRAWABLESYSTEM_H
#define DRAWABLESYSTEM_H

#include <SFML/Graphics.hpp>
#include "Global.h"

class DrawableSystem
{
public:
    void Draw(sf::RenderWindow& window)
    {
        auto drawables = gsManager.CurrentState().get()->drawableComponents;
        window.draw(drawables[0].get()->sprite);

        //std::cout << "draw" << drawables[0].get()->textureUri;
    }
};

#endif //DRAWABLESYSTEM_H

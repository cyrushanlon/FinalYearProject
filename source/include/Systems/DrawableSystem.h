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
        //std::cout << drawables.size();
        for( auto const& x : drawables)
        {
            window.draw(x.get()->sprite);
        }
        //std::cout << "draw" << drawables[0].get()->textureUri;
    }
};

#endif //DRAWABLESYSTEM_H

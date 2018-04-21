#ifndef TEXTSYSTEM_H
#define TEXTSYSTEM_H

#include <SFML/Graphics.hpp>
#include "Global.h"

class TextSystem
{
public:
    void Draw(sf::RenderWindow& window)
    {
        auto state = gsManager.CurrentState().get();

        //for each view we want to go through and see if we want to draw anything
        //this may end up expensive and should be improved
        for( auto const& view : state->views)
        {
            Window.setView(view.second);
            for( auto const& x : state->texts)
            {
                if (view.first == x.get()->GetViewTarget())
                {
                    window.draw(x.get()->text);
                }
            }
        }
    }
};

#endif //TEXTSYSTEM_H

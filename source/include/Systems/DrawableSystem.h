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
    //animating drawables need to think
    void Think(sf::Time dt)
    {
        auto animatables = gsManager.CurrentState().get()->drawableComponents;
        //go through all animatableComponents and see if any frames need changing
        for( auto const& anim : animatables)
        {
            DrawableComponent* x = anim.get();
            //if this one doesnt animate continue
            if (!x->Animates())
                continue;

            //check that the animation exists
            if (x->animations.find(x->currentAnim) != x->animations.end())
            {
                //check if there has been enough time since the last frame
                auto time = x->frameClock.getElapsedTime();
                if (time >= sf::seconds(1 / x->animations.at(x->currentAnim).GetFrameRate()))
                {
                    x->frameClock.restart();
                    auto anim = x->animations.at(x->currentAnim);
                    int nextFrameInt = x->animations.at(x->currentAnim).GetNextFrame();
                    sf::IntRect frame = anim.GetFrame(nextFrameInt);

                    //set texture
                    //x->texture = frame;
                    //x->textureUri = anim->GetFrameURI(nextFrameInt);
                    //x->sprite.setTexture(*x->texture.get());
                    x->sprite.setTextureRect(frame);
                }
            }
        }
    }
};

#endif //DRAWABLESYSTEM_H

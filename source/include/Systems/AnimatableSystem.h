#ifndef ANIMATABLESYSTEM_H
#define ANIMATABLESYSTEM_H

#include <SFML/Graphics.hpp>
#include "Global.h"

class AnimatableSystem
{
public:
    void Think(sf::Time dt)
    {
        auto animatables = gsManager.CurrentState().get()->animatableComponents;
        //go through all animatableComponents and see if any frames need changing
        for( auto const& anim : animatables)
        {
            auto x = anim.second.get();
            //check that the animation exists
            if (x->animations.find(x->currentAnim) != x->animations.end())
            {
                //check if there has been enough time since the last frame
                auto time = x->frameClock.getElapsedTime();
                if (time >= sf::seconds(1 / x->animations[x->currentAnim].GetFrameRate()))
                {
                    x->frameClock.restart();
                    std::string texURI = x->animations[x->currentAnim].GetNextFrame();

                    //set texture
                    x->texture = rscManager.LoadTexture(texURI);
                    x->textureUri = texURI;
                    x->sprite.setTexture(*x->texture.get());
                }
            }
        }
    }
};

#endif //ANIMATABLESYSTEM_H


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
                if (time >= sf::seconds(1 / x->animations.at(x->currentAnim).get()->GetFrameRate()))
                {
                    x->frameClock.restart();
                    auto anim = x->animations.at(x->currentAnim);
                    int nextFrameInt = x->animations.at(x->currentAnim).get()->GetNextFrame();
                    std::shared_ptr<sf::Texture> frame = anim->GetFrame(nextFrameInt);

                    //set texture
                    x->texture = frame;
                    x->textureUri = anim->GetFrameURI(nextFrameInt);
                    x->sprite.setTexture(*x->texture.get());
                }
            }
        }
    }
};

#endif //ANIMATABLESYSTEM_H


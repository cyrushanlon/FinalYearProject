#ifndef ANIMATABLECOMPONENT_H
#define ANIMATABLECOMPONENT_H

#include <map>
#include "Animation.h"
#include "Components/DrawableComponent.h"

class AnimatableComponent : public DrawableComponent
{
public:
    AnimatableComponent();
    ~AnimatableComponent();

    std::map<std::string, Animation> animations;
    std::string currentAnim;
    int currentFrame;
    sf::Clock frameClock;//convert to 1 centralised timer?
};

#endif // ANIMATABLECOMPONENT_H


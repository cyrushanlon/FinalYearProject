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

    std::map<std::string, std::shared_ptr<Animation>> animations;
    std::string currentAnim;
    int currentFrame;
    sf::Clock frameClock;//convert to 1 centralised timer?

    void AddAnimation(std::shared_ptr<Animation> anim);
    void SetAnimation(std::string name);
};

#endif // ANIMATABLECOMPONENT_H


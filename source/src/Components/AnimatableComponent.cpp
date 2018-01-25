#include "Components/AnimatableComponent.h"
#include <iostream>

AnimatableComponent::AnimatableComponent() : DrawableComponent("animatable")
{

}

AnimatableComponent::~AnimatableComponent()
{

}

void AnimatableComponent::AddAnimation(std::shared_ptr<Animation> anim)
{
    this->animations.emplace(anim.get()->GetName(), anim);
}

void AnimatableComponent::SetAnimation(std::string name)
{
    //this->animations.at(this->currentAnim).get()->Reset();
    std::cout << this->animations.size();
    this->currentAnim = name;
    this->currentFrame = 0;
    this->frameClock.restart();
}

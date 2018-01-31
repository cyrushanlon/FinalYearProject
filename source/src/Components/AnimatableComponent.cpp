#include "Components/AnimatableComponent.h"
#include "Global.h"

AnimatableComponent::AnimatableComponent() : DrawableComponent("animatable")
{

}

AnimatableComponent::~AnimatableComponent()
{
    this->texture.reset();
    rscManager.Unload(this->textureUri);
}

void AnimatableComponent::AddAnimation(std::shared_ptr<Animation> anim)
{
    this->animations.emplace(anim.get()->GetName(), anim);
}

void AnimatableComponent::SetAnimation(std::string name)
{
    //this->animations.at(this->currentAnim).get()->Reset();
    this->currentAnim = name;
    this->currentFrame = 0;
    this->frameClock.restart();
}

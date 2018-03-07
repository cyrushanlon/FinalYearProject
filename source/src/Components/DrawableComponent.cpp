#include "Components/DrawableComponent.h"
#include "Global.h"

DrawableComponent::DrawableComponent() : Component("drawable")
{
    this->viewTarget = "main";
    this->animates = false;
}

/*
DrawableComponent::DrawableComponent(std::string uri) : Component("drawable")
{
    DrawableComponent();

    this->textureUri = uri;
    this->texture = rscManager.LoadTexture(uri);
    this->sprite.setTexture(*this->texture.get());
}
*/

DrawableComponent::DrawableComponent(std::string name) : Component(name)
{
    this->viewTarget = "main";
}

DrawableComponent::~DrawableComponent()
{
    //this->texture.reset();
    rscManager.Unload(this->textureUri);
}

sf::Vector2f DrawableComponent::GetPos()
{
    return this->vPos;
}
void DrawableComponent::SetPos(sf::Vector2f pos)
{
    this->vPos = pos;
    this->sprite.setPosition(pos);
}

float DrawableComponent::GetAng()
{
    return this->sprite.getRotation();
}

void DrawableComponent::SetAng(float in)
{
    this->sprite.setRotation(in);
}

sf::Vector2f DrawableComponent::GetOrigin()
{
    return this->sprite.getOrigin();
}

void DrawableComponent::SetOrigin(sf::Vector2f in)
{
    this->sprite.setOrigin(in);
}

void DrawableComponent::SetTexture (std::string uri)
{
    this->texture = rscManager.LoadTexture(uri);
    this->textureUri = uri;
    this->sprite.setTexture(*(this->texture.get()));
    sf::FloatRect bounds = this->sprite.getGlobalBounds();
    this->sprite.setOrigin(bounds.width/2, bounds.height/2);
}

//Animatable
bool DrawableComponent::Animates()
{
    return this->animates;
}
void DrawableComponent::Animates(bool n)
{
    this->animates = n;
}

void DrawableComponent::AddAnimation(Animation anim)
{
    this->animations.emplace(anim.GetName(), anim);
}

void DrawableComponent::SetAnimation(std::string name)
{
    //this->animations.at(this->currentAnim).get()->Reset();
    this->currentAnim = name;
    this->currentFrame = 0;
    this->frameClock.restart();
    this->SetTexture(this->animations[name].getSpritesheetPath());
}

std::string DrawableComponent::GetViewTarget()
{
    return this->viewTarget;
}

void DrawableComponent::SetViewTarget(std::string newTarget)
{
    this->viewTarget = newTarget;
}

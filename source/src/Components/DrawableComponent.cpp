#include "Components/DrawableComponent.h"
#include "Global.h"

DrawableComponent::DrawableComponent() : Component("drawable")
{
    this->viewTarget = "main";
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
    DrawableComponent();
}

DrawableComponent::~DrawableComponent()
{
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

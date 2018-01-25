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

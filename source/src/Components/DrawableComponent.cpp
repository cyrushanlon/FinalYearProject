#include "Components/DrawableComponent.h"
#include "Global.h"

DrawableComponent::DrawableComponent(std::string uri) : Component("drawable")
{
    this->viewTarget = "main";

    this->textureUri = uri;
    this->texture = rscManager.LoadTexture(uri);
    this->sprite.setTexture(*this->texture.get());
}

DrawableComponent::~DrawableComponent()
{
    rscManager.Unload(this->textureUri);
}

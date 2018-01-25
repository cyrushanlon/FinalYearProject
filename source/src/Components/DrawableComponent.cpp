#include "Components/DrawableComponent.h"

DrawableComponent::DrawableComponent() : Component("drawable")
{
    textureUri = "cool";
}

/*
DrawableComponent::~DrawableComponent()
{
    rscManager.Unload(this->textureUri);
}
*/

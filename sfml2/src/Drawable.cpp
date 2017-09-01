#include "Drawable.h"

Drawable::Drawable(ResourceManager* rscManager)
{
    this->manager = rscManager;
}

Drawable::~Drawable()
{
    manager->Unload(this->textureUri);
}

void Drawable::Draw(sf::RenderWindow *window)
{
    window->draw(this->sprite);
}

sf::Vector2f Drawable::GetPos()
{
    return this->sprite.getPosition();
}

//TODO
//Move this into the resource management system once it is created
void Drawable::SetTexture(std::string uri)
{
    this->texture = this->manager->Load(uri);
    this->textureUri = uri;

    this->sprite.setTexture(this->texture);
}

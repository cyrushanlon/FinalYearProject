#include "Drawable.h"

#include "Global.h"

Drawable::Drawable(std::string ID, ResourceManager* rscManager) : Point(ID) //call base constructor
{
    this->manager = rscManager;
    Drawables[this->ID] = this;
}

Drawable::Drawable(std::string ID, ResourceManager* rscManager, std::string texturePath) : Drawable(ID, rscManager)//call other constructor
{
    this->SetTexture(texturePath);
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

void Drawable::SetTexture(std::string uri)
{
    //dont really want a local version of the texture but sometimes we may want to have some special texture specific behaviour
    this->texture = this->manager->Load(uri);
    this->textureUri = uri;

    this->sprite.setTexture(this->texture);
}

void Drawable::SetPos(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

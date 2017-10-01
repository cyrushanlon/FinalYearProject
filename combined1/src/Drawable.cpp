#include "Drawable.h"

#include "Global.h"

Drawable::Drawable(std::string ID) : Point(ID) //call base constructor
{
    Drawables[this->ID] = this;
}

Drawable::Drawable(std::string ID, std::string texturePath) : Drawable(ID)//call other constructor
{
    this->SetTexture(texturePath);
}

Drawable::~Drawable()
{
    rscManager.Unload(this->textureUri);
}

void Drawable::Draw(sf::RenderWindow *window)
{
    window->draw(this->sprite);
}

void Drawable::SetTexture(std::string uri)
{
    //dont really want a local version of the texture but sometimes we may want to have some special texture specific behaviour
    this->texture = rscManager.Load(uri);
    this->textureUri = uri;

    this->sprite.setTexture(this->texture);
}

sf::Vector2f Drawable::GetPos()
{
    return this->sprite.getPosition();
}

void Drawable::SetPos(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

float Drawable::GetAng()
{
    return this->sprite.getRotation();
}

void Drawable::SetAng(float ang)
{
    this->sprite.setRotation(ang);
}

sf::Vector2f Drawable::GetOrigin()
{
    return this->sprite.getOrigin();
}

void Drawable::SetOrigin(sf::Vector2f origin)
{
    this->sprite.setOrigin(origin);
}

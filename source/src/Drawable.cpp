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
    this->texture = rscManager.LoadTexture(uri);
    this->textureUri = uri;

    this->sprite.setTexture(*this->texture.get());
}

std::shared_ptr<sf::Texture> Drawable::GetTexture()
{
    return this->texture;
}

sf::Sprite Drawable::GetSprite()
{
    return this->sprite;
}

sf::Vector2f Drawable::GetPos()
{
    return this->virtualPos;
}

void Drawable::SetPos(sf::Vector2f pos)
{
    this->virtualPos = pos;
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

#include "Drawable.h"

Drawable::Drawable()
{
    //ctor
}

Drawable::~Drawable()
{
    //dtor
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
void Drawable::SetTexture(std::string TexturePath)
{
    this->texture.loadFromFile(TexturePath);

    //transparency mask on magenta
    auto img = this->texture.copyToImage();
    img.createMaskFromColor(sf::Color::Magenta);
    this->texture.loadFromImage(img);

    this->sprite.setTexture(this->texture);
}

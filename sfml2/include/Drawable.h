#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Drawable
{
public:
    Drawable(ResourceManager*);
    virtual ~Drawable();
    virtual void Draw(sf::RenderWindow*);
    sf::Vector2f GetPos();

    void SetTexture(std::string);
protected:

private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::string textureUri;
    ResourceManager* manager;
};

#endif // DRAWABLE_H

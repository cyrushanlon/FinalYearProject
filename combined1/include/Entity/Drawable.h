#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Entity/Point.h"

class Drawable : public Point
{
public:
    Drawable(ResourceManager*);
    Drawable(ResourceManager*, std::string);

    virtual ~Drawable();
    virtual void Draw(sf::RenderWindow*);

    virtual sf::Vector2f GetPos();
    virtual void SetPos(sf::Vector2f);

    //Drawable only, we dont want these to be virtual
    void SetTexture(std::string);
protected:

private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::string textureUri; //used in the dtor to free the resource
    ResourceManager* manager;
};

#endif // DRAWABLE_H

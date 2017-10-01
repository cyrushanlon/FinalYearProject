#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include "Entity/Point.h"

class Drawable : public Point
{
public:
    Drawable(std::string);
    Drawable(std::string, std::string);

    virtual ~Drawable();
    virtual void Draw(sf::RenderWindow*);

    virtual sf::Vector2f GetPos();
    virtual void SetPos(sf::Vector2f);
    virtual float GetAng();
    virtual void SetAng(float);
    virtual sf::Vector2f GetOrigin();
    virtual void SetOrigin(sf::Vector2f);

    //Drawable only, we dont want these to be virtual
    void SetTexture(std::string);
protected:

private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::string textureUri; //used in the dtor to free the resource
};

#endif // DRAWABLE_H

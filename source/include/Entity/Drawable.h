#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity/Point.h"

class Drawable : public Point
{
public:
    Drawable(std::string);
    Drawable(std::string, std::string);
    Drawable(std::string, std::string, std::string);

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
    std::shared_ptr<sf::Texture> GetTexture();
    sf::Sprite GetSprite();
    //view
    std::string GetViewTarget();
    void SetViewTarget(std::string);
protected:

private:
    sf::Vector2f virtualPos;
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    std::string textureUri; //used in the dtor to free the resource

    std::string viewTarget; //holds the id of the view that the drawable should be drawn onto
};

#endif // DRAWABLE_H

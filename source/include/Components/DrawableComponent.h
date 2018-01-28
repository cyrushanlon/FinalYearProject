#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "Components/Component.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent();
    ~DrawableComponent();

    sf::Vector2f vPos; //virtual position

    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    std::string textureUri; //used in the dtor to free the resource
    std::string viewTarget;

    virtual sf::Vector2f GetPos();
    virtual void SetPos(sf::Vector2f);
    virtual float GetAng();
    virtual void SetAng(float);
    virtual sf::Vector2f GetOrigin();
    virtual void SetOrigin(sf::Vector2f);

    virtual void SetTexture (std::string); 
protected:
    //used for classes that inherit from this one, such as AnimatableComponent
    DrawableComponent(std::string name);
};

#endif // DRAWABLECOMPONENT_H

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

    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    std::string textureUri; //used in the dtor to free the resource
    std::string viewTarget;
protected:
    //used for classes that inherit from this one, such as AnimatableComponent
    DrawableComponent(std::string name);
};

#endif // DRAWABLECOMPONENT_H

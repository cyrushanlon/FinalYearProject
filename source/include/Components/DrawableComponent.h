#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "Components/Component.h"
#include "Animation.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent();
    virtual ~DrawableComponent();

    sf::Vector2f vPos; //virtual position

    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture; //used when drawing
    std::string textureUri; //used in the dtor to free the resource
    std::string viewTarget;

    virtual sf::Vector2f GetPos();
    virtual void SetPos(sf::Vector2f);
    virtual float GetAng();
    virtual void SetAng(float);
    virtual sf::Vector2f GetOrigin();
    virtual void SetOrigin(sf::Vector2f);

    virtual void SetTexture (std::string);

    //animatable stuff:
    bool Animates();
    void Animates(bool);

    std::map<std::string, Animation> animations;
    std::string currentAnim;
    int currentFrame;
    sf::Clock frameClock;//convert to 1 centralised timer?

    void AddAnimation(Animation anim);
    void SetAnimation(std::string name);
protected:
    //used for classes that inherit from this one, such as AnimatableComponent
    DrawableComponent(std::string name);
private:
    bool animates;
};

#endif // DRAWABLECOMPONENT_H

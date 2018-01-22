#include "Animatable.h"

Animatable::Animatable(std::string id) : Drawable(id)
{

    //ctor
}

Animatable::Animatable(std::string id, std::string viewTarget) : Drawable(id)
{
    this->SetViewTarget(viewTarget);
}

Animatable::~Animatable()
{
    //dtor
}

void Animatable::Think(sf::Time dt)
{
    //check that the animation exists
    if (this->animations.find(this->currentAnim) != this->animations.end())
    {
        //check if there has been enough time since the last frame
        auto time = this->frameClock.getElapsedTime();
        if (time >= sf::seconds(1 / this->animations[this->currentAnim].GetFrameRate()))
        {
            this->frameClock.restart();
            std::string texURI = this->animations[this->currentAnim].GetNextFrame();
            this->SetTexture(texURI);
        }
    }
}

void Animatable::SetAnimation(std::string name)
{
    //check that the animation exists
    if (this->animations.find(name) != this->animations.end())
    {
        this->animations[this->currentAnim].Reset();

        this->currentAnim = name;
        this->currentFrame = 0;
        this->frameClock.restart();
        //reset old animation to frame 0
    }
}

void Animatable::SetFrame(int frame)
{
    /*
    //check that the animation exists
    if (this->animations.count(this->currentAnim))
    {
        this->currentFrame = frame;

    }
    */
}

void Animatable::AddAnimation(std::string name, Animation newAnim)
{
    this->animations.emplace(name, newAnim);
}

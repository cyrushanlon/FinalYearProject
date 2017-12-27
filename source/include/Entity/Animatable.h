#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include <map>

#include "Drawable.h"
#include "Animation.h"

class Animatable : public Drawable
{
    public:
        Animatable(std::string id);
        virtual ~Animatable();

        //change the frame based on dt
        virtual void Think(sf::Time dt);

        //set the animation from the animations map with the given name
        void SetAnimation(std::string name);
        //set the frame to the target frame within the current animation
        void SetFrame(int frame);

        //add a new animation to the animations map
        void AddAnimation(std::string name, Animation newAnim);
    protected:

    private:
        std::map<std::string, Animation> animations;
        std::string currentAnim;
        int currentFrame;
        sf::Clock frameClock;
};

#endif // ANIMATABLE_H

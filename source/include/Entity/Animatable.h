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

        void SetAnimation(std::string name);
        void SetFrame(int frame);

        void AddAnimation(Animation newAnim);
    protected:

    private:
        std::map<std::string, Animation>
        std::string currentFrame;
};

#endif // ANIMATABLE_H

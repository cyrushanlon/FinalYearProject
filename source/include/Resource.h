#ifndef RESOURCE_H
#define RESOURCE_H

#include<SFML/Graphics.hpp>

//will also hold sounds and etc here
class Resource
{
    public:
        Resource();
        virtual ~Resource();

        sf::Texture Texture;
        unsigned Useage;

    protected:

    private:
};

#endif // RESOURCE_H

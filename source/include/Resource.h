#ifndef RESOURCE_H
#define RESOURCE_H

#include<SFML/Graphics.hpp>

#include "ResourceInterface.h"

template <class T>
class Resource : public ResourceInterface
{
    public:
        //Resource();
        //virtual ~Resource();

        Resource()
        {
            //ctor
        }
        virtual ~Resource()
        {
            //dtor
        }

        T resource;
        unsigned Useage;

    protected:

    private:
};

#endif // RESOURCE_H

#ifndef RESOURCE_H
#define RESOURCE_H

#include<memory>

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

        std::shared_ptr<T> resource;
        unsigned Useage;

    protected:

    private:
};

#endif // RESOURCE_H

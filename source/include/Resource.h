#ifndef RESOURCE_H
#define RESOURCE_H

#include<memory>
#include <iostream>

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
        Resource(std::shared_ptr<T> rsc, unsigned usage)
        {
            this->resource = rsc;
            this->Useage = usage;
        }
        virtual ~Resource()
        {
            std::cout << "oh no!!" << std::endl;
            //dtor
        }

        std::shared_ptr<T> resource;

    protected:

    private:
};

#endif // RESOURCE_H

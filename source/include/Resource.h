#ifndef RESOURCE_H
#define RESOURCE_H

#include<memory>

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
        Resource(std::shared_ptr<T> rsc)//, unsigned usage)
        {
            this->resource = rsc;
            //this->Useage = usage;
        }
        virtual ~Resource()
        {
            //dtor
        }
        long Usage()
        {
            return this->resource.use_count();
        }

        std::shared_ptr<T> resource;

    protected:

    private:
};

#endif // RESOURCE_H

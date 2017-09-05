#ifndef POINT_H
#define POINT_H

#include <SFML/System.hpp>

//a none drawing entity that thinks
class Point
{
    public:
        Point();
        virtual ~Point(){}
        virtual void Think(sf::Time);

        std::string GetID();
        void SetID(std::string);
    protected:

    private:
        std::string ID;
};

#endif // POINT_H

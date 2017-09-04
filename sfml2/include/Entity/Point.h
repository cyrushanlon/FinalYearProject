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
    protected:

    private:
};

#endif // POINT_H

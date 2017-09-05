#ifndef POINT_H
#define POINT_H

#include <SFML/System.hpp>

//a none drawing entity that thinks
class Point
{
    public:
        Point(std::string);
        virtual ~Point(){}
        virtual void Think(sf::Time);

        std::string GetID();
        void SetID(std::string);
    protected:
        const std::string ID;
    private:
};

#endif // POINT_H

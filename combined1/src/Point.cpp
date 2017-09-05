#include "Entity/Point.h"

#include "Global.h"

Point::Point()
{
    Points.push_back(this);
}

void Point::Think(sf::Time dt)
{

}

std::string Point::GetID()
{
    return this->ID;
}

void Point::SetID(std::string newID)
{
    //check for clashes?
    this->ID = newID;
}

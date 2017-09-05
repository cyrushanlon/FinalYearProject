#include "Entity/Point.h"

#include "Global.h"

//set the ID in the initializer list as it is a const val
Point::Point(std::string inID) : ID(inID)
{
    Points[ID] = this;
}

void Point::Think(sf::Time dt)
{

}

std::string Point::GetID()
{
    return this->ID;
}

/* we dont want the ID to be changeable
void Point::SetID(std::string newID)
{
    //check for clashes?
    this->ID = newID;
}
*/

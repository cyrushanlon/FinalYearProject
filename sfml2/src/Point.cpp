#include "Entity/Point.h"

#include "Global.h"

void Point::Think(sf::Time dt)
{
    Points.push_back(this);
}

#include "Components/Component.h"

Component::Component(std::string name)
{
    this->name = name;
}

std::string Component::Name()
{
    return this->name;
}
void Component::SetParent(std::string parentID)
{
    this->parentID = parentID;
}

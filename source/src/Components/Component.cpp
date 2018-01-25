#include "Components/Component.h"

Component::Component(std::string ID)
{
    this->name = ID;
}

std::string Component::Name()
{
    return this->name;
}
void Component::SetParent(std::shared_ptr<Entity> parent)
{
    this->parent = parent;
}

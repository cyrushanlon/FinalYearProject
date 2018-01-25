#ifndef COMPONENT_H
#define COMPONENT_H

#include "Components/Entity.h"

class Entity;

class Component
{
public:
    Component(std::string);

    std::string Name();
    void SetParent(Entity* parent);
private:
    std::string name;
    Entity* parent;
};

#endif //COMPONENT_H

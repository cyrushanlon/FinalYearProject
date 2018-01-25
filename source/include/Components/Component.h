#ifndef COMPONENT_H
#define COMPONENT_H

#include "Components/Entity.h"

class Entity;

class Component
{
public:
    Component(std::string ID);

    std::string Name();
    void SetParent(std::shared_ptr<Entity> parent);
private:
    std::string name;
    std::shared_ptr<Entity> parent;
};

#endif //COMPONENT_H

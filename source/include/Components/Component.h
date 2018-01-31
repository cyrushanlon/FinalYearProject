#ifndef COMPONENT_H
#define COMPONENT_H

#include "Components/Entity.h"

class Entity;

class Component
{
public:
    Component(std::string);

    std::string Name();
    void SetParent(std::string parentID);
    std::string GetParent();
private:
    std::string name;
    std::string parentID;
};

#endif //COMPONENT_H

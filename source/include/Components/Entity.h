#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>
#include "Components/Component.h"

class Component;

class Entity
{
public:
    Entity(std::string);

    std::string GetID();
    bool HasComponent(std::string);
    bool AddComponent(std::shared_ptr<Component> comp);
private:
    std::string ID;
};

#endif // ENTITY_H

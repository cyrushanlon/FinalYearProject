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
    ~Entity();

    std::string GetID();
    bool HasComponent(std::string);
    std::shared_ptr<Component> AddComponent(std::shared_ptr<Component> comp);
    void RemoveDrawableComponent();
    void RemovePhysicsComponent();
private:
    std::string ID;
};

#endif // ENTITY_H

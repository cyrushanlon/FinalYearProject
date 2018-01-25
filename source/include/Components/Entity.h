#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class Entity
{
public:
    Entity()
    {

    }

    std::string GetID()
    {

    }
    bool HasComponent(std::string)
    {

    }
    //std::shared_ptr<Component> GetComponent(std::string);
    bool AddComponent()
    {
        gsManager.CurrentState().get()->drawableComponents.push_back(std::make_shared<DrawableComponent>());
    }
private:
    //std::vector<std::shared_ptr<Component> > components;
    std::string ID;
};

#endif // ENTITY_H

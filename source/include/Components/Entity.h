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
    bool AddComponent(std::shared_ptr<Component> comp)
    {
        //make this more generic rather than a bunch of if else
        std::string name = comp.get()->Name();
        if (name == "drawable")
            gsManager.CurrentState().get()->drawableComponents.push_back(std::static_pointer_cast<DrawableComponent>(comp));
        else
            std::cout << "unhandled " << name;
    }
private:
    //std::vector<std::shared_ptr<Component> > components;
    std::string ID;
};

#endif // ENTITY_H

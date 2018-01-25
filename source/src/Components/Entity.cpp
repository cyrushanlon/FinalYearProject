#include "Components/Entity.h"
#include "Global.h"

Entity::Entity(std::string ID)
{
    this->ID = ID;
}

std::string Entity::GetID()
{
    return this->ID;
}

bool Entity::AddComponent(std::shared_ptr<Component> comp)
{
    comp.get()->SetParent(this->ID);
    //make this more generic rather than a bunch of if else
    std::string name = comp.get()->Name();

    auto gs = gsManager.CurrentState().get();

    if (name == "drawable")
    {
        gs->drawableComponents.push_back(std::static_pointer_cast<DrawableComponent>(comp));
    }
    else if (name == "animatable")
    {
        gs->animatableComponents[this->ID] = (std::static_pointer_cast<AnimatableComponent>(comp));
        gs->drawableComponents.push_back(std::static_pointer_cast<DrawableComponent>(comp));
    }
    else
        std::cout << "unhandled " << name;
}

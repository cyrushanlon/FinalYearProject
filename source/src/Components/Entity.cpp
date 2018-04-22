#include "Components/Entity.h"
#include "Global.h"

Entity::Entity(std::string ID)
{
    this->ID = ID;

    gsManager.CurrentState().get()->entities[ID] = std::shared_ptr<Entity>(this);
}

Entity::~Entity()
{
    this->RemoveDrawableComponent();
    this->RemovePhysicsComponent();

    Gamestate* gs = gsManager.CurrentState().get();

    gs->entities.erase(this->ID);
}

std::string Entity::GetID()
{
    return this->ID;
}

std::shared_ptr<Component> Entity::AddComponent(std::shared_ptr<Component> comp)
{
    comp.get()->SetParent(this->ID);
    //make this more generic rather than a bunch of if else
    std::string name = comp.get()->Name();

    auto gs = gsManager.CurrentState().get();

    if (name == "drawable")
    {
        gs->drawableComponents.push_back(std::static_pointer_cast<DrawableComponent>(comp));
    }
    else if (name == "physics")
    {
        gs->physicsComponents.push_back(std::static_pointer_cast<PhysicsComponent>(comp));
    }
    else
        std::cout << "unhandled " << name;

    return comp;
}

void Entity::RemoveDrawableComponent()
{
    Gamestate* gs = gsManager.CurrentState().get();

    for (int i = 0; i < gs->drawableComponents.size(); i++)
    {
        auto cur = gs->drawableComponents.at(i);
        if (cur.get()->GetParent() == this->GetID())
        {
            gs->drawableComponents.erase(gs->drawableComponents.begin() + i);
            //delete cur.get();
            return;
        }
    }
}

void Entity::RemovePhysicsComponent()
{
    Gamestate* gs = gsManager.CurrentState().get();

    for (int i = 0; i < gs->physicsComponents.size(); i++)
    {
        auto cur = gs->physicsComponents.at(i);
        if (cur.get()->GetParent() == this->GetID())
        {
            gs->physicsComponents.erase(gs->physicsComponents.begin() + i);
            //delete cur.get();
            return;
        }
    }
}

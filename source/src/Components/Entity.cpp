#include "Components/Entity.h"
#include "Global.h"

Entity::Entity()
{

}

bool Entity::AddComponent(std::shared_ptr<Component> comp)
{
    comp.get()->SetParent(this);
    //make this more generic rather than a bunch of if else
    std::string name = comp.get()->Name();

    if (name == "drawable")
        gsManager.CurrentState().get()->drawableComponents.push_back(std::static_pointer_cast<DrawableComponent>(comp));
    else
        std::cout << "unhandled " << name;
}

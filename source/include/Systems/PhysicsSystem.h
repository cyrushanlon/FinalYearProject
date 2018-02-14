#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Global.h"

#include "Components/DrawableComponent.h"
#include "Components/PhysicsComponent.h"

class PhysicsSystem
{
public:
    //positions of sprites needs to be set
    void Think(sf::Time dt)
    {
        auto physicsComponents = gsManager.CurrentState().get()->physicsComponents;
        //go through all animatableComponents and see if any frames need changing
        for( auto const& comp : physicsComponents)
        {
            std::string id = comp->GetParent();
            std::shared_ptr<DrawableComponent> drawable = gsManager.CurrentState().get()->GetDrawable(id);
            if (!drawable) //if the drawable component doesnt exist
                continue;

            b2Vec2 pos = comp->GetPosition();
            //scale the m positions into pixels for drawing
            drawable.get()->SetPos(sf::Vector2f(pos.x * 32, pos.y * -32));
            drawable.get()->SetAng(comp->GetAngle() * (180/3.14159265358979));
        }
    }
};

#endif // PHYSICSSYSTEM_H

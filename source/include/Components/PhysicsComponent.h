#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Components/Component.h"
#include "Box2D/Box2D.h"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(b2BodyDef bodyDef, b2FixtureDef fixDef, float width, float height);
    virtual ~PhysicsComponent();

    void SetBodyTransform(b2Vec2 pos, float angle);
    void SetBodyTransform(b2Vec2 pos);
    void SetBodyTransform(float angle);

    b2Vec2 GetPosition();
    float GetAngle();
private:
    b2Body* body;
    b2Fixture* fixture;
    b2PolygonShape shape;
};

#endif // PHYSICSCOMPONENT_H

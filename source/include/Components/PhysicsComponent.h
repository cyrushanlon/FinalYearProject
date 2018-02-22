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

    void ApplyForce(b2Vec2, b2Vec2, bool);
    void ApplyForceToCenter(b2Vec2 force, bool);

    void ApplyImpulse(b2Vec2, b2Vec2, bool);
    void ApplyImpulseToCenter(b2Vec2 force, bool);

    b2Vec2 GetPosition();
    float GetAngle();

    b2Vec2 GetLinearVelocity();
private:
    b2Body* body;
    b2Fixture* fixture;
    b2PolygonShape shape;
};

#endif // PHYSICSCOMPONENT_H

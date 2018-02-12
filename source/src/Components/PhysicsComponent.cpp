#include "Components/PhysicsComponent.h"
#include "Global.h"

//TODO
//add support for other shapes than box

PhysicsComponent::PhysicsComponent(b2BodyDef bodyDef, b2FixtureDef fixDef, float width, float height) : Component("physics")
{
    body = world.CreateBody(&bodyDef);
    shape.SetAsBox(width, height);
    fixture = body->CreateFixture(&fixDef);
}

PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::SetBodyTransform(b2Vec2 pos, float angle)
{
    this->body->SetTransform(pos, angle);
}
void PhysicsComponent::SetBodyTransform(b2Vec2 pos)
{
    this->body->SetTransform(pos, body->GetAngle());
}
void PhysicsComponent::SetBodyTransform(float angle)
{
    this->body->SetTransform(body->GetPosition(), angle);
}

b2Vec2 PhysicsComponent::GetPosition()
{
    return this->body->GetPosition();
}
float PhysicsComponent::GetAngle()
{
    return this->body->GetAngle();
}

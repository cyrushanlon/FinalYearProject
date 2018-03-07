#include "Components/PhysicsComponent.h"
#include "Global.h"

//TODO
//add support for other shapes than box

PhysicsComponent::PhysicsComponent(b2BodyDef bodyDef, b2FixtureDef fixDef, float width, float height) : Component("physics")
{
    body = world.CreateBody(&bodyDef);
    shape.SetAsBox(width/2, height/2); //box2d uses half width and height
    fixDef.shape = &shape;
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

void PhysicsComponent::ApplyForce(b2Vec2 force, b2Vec2 point, bool wake)
{
    this->body->ApplyForce(force, point, wake);
}
void PhysicsComponent::ApplyForceToCenter(b2Vec2 force, bool wake)
{
    this->body->ApplyForceToCenter(force, wake);
}

void PhysicsComponent::ApplyImpulse(b2Vec2 force, b2Vec2 point, bool wake)
{
    this->body->ApplyLinearImpulse(force, point, wake);
}
void PhysicsComponent::ApplyImpulseToCenter(b2Vec2 force, bool wake)
{
    this->body->ApplyLinearImpulseToCenter(force, wake);
}

b2Vec2 PhysicsComponent::GetLinearVelocity()
{
    return this->body->GetLinearVelocity();
}
void PhysicsComponent::SetLinearVelocity(b2Vec2 newVel)
{
    this->body->SetLinearVelocity(newVel);
}

void PhysicsComponent::ApplyTorque(float32 torque, bool wake)
{
    this->body->ApplyTorque(torque, wake);
}
void PhysicsComponent::ApplyAngularImpulse(float32 torque, bool wake)
{
    this->body->ApplyAngularImpulse(torque, wake);
}

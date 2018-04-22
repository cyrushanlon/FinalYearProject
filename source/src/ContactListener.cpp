#include "ContactListener.h"

#include <iostream>
#include "Components/PhysicsComponent.h"
#include "Global.h"

ContactListener::ContactListener()
{
    //ctor
}

ContactListener::~ContactListener()
{
    //dtor
}

void ContactListener::EndContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyAUserData && bodyBUserData )
    {
        PhysicsComponent* a = static_cast<PhysicsComponent*>(bodyAUserData);
        PhysicsComponent* b = static_cast<PhysicsComponent*>(bodyBUserData);

        Lua.HookEndContact(a->GetParent(), b->GetParent());
    }
}

void ContactListener::BeginContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyAUserData && bodyBUserData )
    {
        PhysicsComponent* a = static_cast<PhysicsComponent*>(bodyAUserData);
        PhysicsComponent* b = static_cast<PhysicsComponent*>(bodyBUserData);

        Lua.HookBeginContact(a->GetParent(), b->GetParent());
    }
}

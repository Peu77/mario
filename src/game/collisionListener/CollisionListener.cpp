//
// Created by peu77 on 2/7/22.
//

#include "CollisionListener.h"
#include "../objects/GameObject.h"

CollisionListener::CollisionListener(b2World &physicsWorld) {
    physicsWorld.SetContactListener(this);
}

void CollisionListener::BeginContact(b2Contact *contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    GameObject* objA = (GameObject*)bodyA->GetUserData().pointer;
    GameObject* objB = (GameObject*)bodyB->GetUserData().pointer;

    if (objA && objB)
    {
        objA->onCollision(objB);
        objB->onCollision(objA);
    }
}

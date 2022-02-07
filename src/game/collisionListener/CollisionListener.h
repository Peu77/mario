//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_COLLISIONLISTENER_H
#define MARIO_COLLISIONLISTENER_H

#include "../Box2dInclude.h"

class CollisionListener: public b2ContactListener {
public:
    CollisionListener(b2World& physicsWorld);
    void BeginContact(b2Contact* contact) override;
};


#endif //MARIO_COLLISIONLISTENER_H

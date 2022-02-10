//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_GAMEOBJECT_H
#define MARIO_GAMEOBJECT_H

#include "../GlmInclude.h"
#include "../Box2dInclude.h"
#include "../renderer/Renderer.h"
#include "../collisionListener/CollisionListener.h"
#include "vector"

static float PIXEL_TO_M = 150.0f;

class GameObject {
public:
    virtual void update(float deltaTime) = 0;

    virtual void render() = 0;

    virtual void onCollision(GameObject *object) = 0;

public:
    bool shouldDelete = false;
    b2Body *body;
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
    std::string tag;
};

#endif //MARIO_GAMEOBJECT_H

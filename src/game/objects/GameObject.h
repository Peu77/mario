//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_GAMEOBJECT_H
#define MARIO_GAMEOBJECT_H


#include "../Box2dInclude.h"
#include "../renderer/Renderer.h"
#include "vector"
#include "../physic/Body.h"

static float PIXEL_TO_M = 150.0f;

class GameObject {
public:
    virtual void update(float deltaTime) {
        //position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};
    };

    virtual void render() = 0;

    virtual void onCollision() = 0;

public:
    bool shouldDelete = false;
    Body *body;
    float rotation;
    glm::vec2 scale;
    std::string tag;
};

#endif //MARIO_GAMEOBJECT_H

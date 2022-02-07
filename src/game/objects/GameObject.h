//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_GAMEOBJECT_H
#define MARIO_GAMEOBJECT_H

#include "../GlmInclude.h"
#include "../Box2dInclude.h"
#include "../renderer/Renderer.h"

class GameObject {
public:
    virtual void update(float deltaTime) =0;

    virtual void render() = 0;

    virtual void onCollision(GameObject* object) = 0;

public:
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
};

#endif //MARIO_GAMEOBJECT_H

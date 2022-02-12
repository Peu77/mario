//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_GAMEOBJECT_H
#define MARIO_GAMEOBJECT_H


#include "../renderer/Renderer.h"
#include "vector"

static float GRAVITY = 40.0f;

struct Body;

class GameObject {
public:
    virtual void update(float deltaTime) {
    };

    virtual void render() = 0;

    virtual void onCollision() = 0;

public:
    bool shouldDelete = false;
    Body *body;
    float rotation;
    glm::vec2 scale;
};


struct Body {
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 vel;
    glm::vec2 friction;
    Body* contact[4];
    void* data;
    bool dynamic = false;
    std::string tag;
};

#endif //MARIO_GAMEOBJECT_H

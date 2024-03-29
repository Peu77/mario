//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_GAMEOBJECT_H
#define MARIO_GAMEOBJECT_H


#include "../renderer/Renderer.h"
#include "vector"

static float GRAVITY = 40.0f;

struct Body;

enum Type {
    FOREGROUND,
    BACKGROUND
};

class GameObject {
public:
    virtual ~GameObject() {
        std::cout << "destroy object" << std::endl;
    }

    virtual void update(float deltaTime) {
    };

    virtual void render() = 0;

    virtual void onCollision() = 0;

    virtual float getVelocityX(float &velocity, float x, float delta) {
        return velocity * delta + x;
    };

public:
    bool shouldDelete = false;
    Body *body;
    float rotation;
    glm::vec2 scale;
    Type type = Type::FOREGROUND;

    //variables for background objects
    std::string texturePath = "none";
    float textureWidth = 0;
    float textureHeight = 0;

};


struct Body {
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 vel;
    glm::vec2 friction;
    Body *contact[4];
    void *data;
    bool dynamic = false;
    bool canCollide = true;
    std::string tag;
};

#endif //MARIO_GAMEOBJECT_H

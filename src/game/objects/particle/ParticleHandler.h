//
// Created by peu77 on 2/14/22.
//

#ifndef MARIO_PARTICLEHANDLER_H
#define MARIO_PARTICLEHANDLER_H

#include "iostream"
#include "../../texture/Texture.h"
#include "../../GlmInclude.h"
#include "../../renderer/Renderer.h"
#include "vector"

struct Particle {
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 vel;
    int lifetime = 50;
};

class ParticleHandler {
    std::vector<Particle *> particles;
    float animationSpeed = 0.02f;
    float animationTime = animationSpeed;

public:
    ~ParticleHandler();

    void update(float deltaTime);

    void render(Texture* texture);

    void spawnNew(glm::vec2 pos, glm::vec2 vel, float deltaTime);
};


#endif //MARIO_PARTICLEHANDLER_H

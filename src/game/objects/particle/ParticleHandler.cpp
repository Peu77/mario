//
// Created by peu77 on 2/14/22.
//

#include "ParticleHandler.h"

void ParticleHandler::update(float deltaTime) {
    for (int i = 0; i < particles.size(); i++) {
        auto item = particles[i];
        item->pos += item->vel * deltaTime;
        item->lifetime--;

        if (item->lifetime <= 0)
            particles.erase(particles.begin() + i);
    }

}

void ParticleHandler::render(Texture* texture) {
        for (auto &item: this->particles)
            Renderer::drawQuad(item->pos, item->size, texture);
}

void ParticleHandler::spawnNew(glm::vec2 pos, glm::vec2 vel, float deltaTime) {
    if (animationTime > 0) {
        animationTime -= deltaTime;
        return;
    }
    animationTime = animationSpeed;
    float rsize = (rand() % 50) / 2.0f;
    float rvel = (rand() % (100) - 50);
    auto particle = new Particle();
    particle->pos = pos;
    particle->vel = {rvel, std::abs(rvel)};
    particle->size = {rsize, rsize};
    particles.push_back(particle);
}

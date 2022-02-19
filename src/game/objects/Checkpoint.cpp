//
// Created by peu77 on 2/14/22.
//

#include "Checkpoint.h"

Checkpoint::Checkpoint(glm::vec2 spawnPosition) {
    texture = getTexture("res/textures/checkpoint.png");
    scale = {300, 100};
    body = new Body();
    body->tag = "checkpoint";
    body->friction = {0.8f, 0.9f};
    body->pos = spawnPosition;
    body->size = scale;
    body->data = this;

    particle1 = getTexture("res/textures/particle.png");
    particle2 = getTexture("res/textures/particle-hover.png");
    particle = particle1;
    this->particleHandler = new ParticleHandler();

}

Checkpoint::~Checkpoint() {

}

void Checkpoint::update(float deleteTime) {
    particleHandler->update(deleteTime);
    float r = (rand() % 300);
    particleHandler->spawnNew({body->pos.x - 50 + r, body->pos.y + body->size.y / 2}, {130, 140}, deleteTime);
    GameObject::update(deleteTime);
}

void Checkpoint::render() {
    Renderer::drawQuad({body->pos.x + 100, body->pos.y}, scale, texture);

    particleHandler->render(particle);
}

void Checkpoint::onCollision() {

}

void Checkpoint::active() {
    if (particle != particle2) {
        particle = particle2;
    }
}

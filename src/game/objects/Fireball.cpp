//
// Created by peu77 on 2/19/22.
//

#include "Fireball.h"

Fireball::Fireball(glm::vec2 spawnPosition, glm::vec2 velocity, GameObject *shooter) {
    this->texture = getTexture("res/textures/fireball.png");
    this->shooter = shooter;
    scale = {40, 40};
    body = new Body();
    body->tag = "fireball";
    body->data = this;
    body->dynamic = true;
    body->friction = {0.8f, 0.9f};
    body->pos = spawnPosition;
    body->vel = velocity;
    body->size = scale;
}

void Fireball::update(float deleteTime) {
    GameObject::update(deleteTime);
}

void Fireball::render() {
    Renderer::drawQuad({body->pos.x + body->size.x / 2 - 50, body->pos.y + body->size.y / 2 - 50}, scale, texture);
}

void Fireball::onCollision() {
        this->shouldDelete = true;
}

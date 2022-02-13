//
// Created by peu77 on 2/7/22.
//

#include "Brick.h"


Brick::Brick(glm::vec2 spawnPosition) {
    texture = getTexture("res/textures/brick.png");
    scale = {100, 100};
    body = new Body();
    body->tag = "brick";
    body->friction = {0.8f, 0.9f};
    body->pos = spawnPosition;
    body->size = scale;
}

Brick::~Brick() {
}

void Brick::update(float deleteTime) {
}

void Brick::render() {
    Renderer::drawQuad(body->pos, scale, texture);
}

void Brick::onCollision() {

}

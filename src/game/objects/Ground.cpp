//
// Created by peu77 on 2/18/22.
//

#include "Ground.h"

Ground::Ground(glm::vec2 spawnPosition) {
    texture = getTexture("res/textures/ground.png");
    scale = {100, 100};
    body = new Body();
    body->tag = "ground";
    body->friction = {0.8f, 0.9f};
    body->pos = spawnPosition;
    body->size = scale;
}

void Ground::update(float deleteTime) {
    GameObject::update(deleteTime);
}

void Ground::render() {
    Renderer::drawQuad(body->pos, scale, texture);
}

void Ground::onCollision() {

}

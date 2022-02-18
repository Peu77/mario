//
// Created by peu77 on 2/17/22.
//

#include "Bitcoin.h"

Bitcoin::Bitcoin(glm::vec2 spawnPosition) {
    texture = getTexture("res/textures/bitcoin.png");
    scale = {100, 100};
    body = new Body();
    body->tag = "bitcoin";
    body->friction = {0.8f, 0.9f};
    body->data = this;
    body->pos = spawnPosition;
    body->size = scale;
    body->canCollide = false;


    Renderer::getRenderData()->lights->push_back(spawnPosition.x);
    Renderer::getRenderData()->lights->push_back(spawnPosition.y);
}

Bitcoin::~Bitcoin() {
    auto light = Renderer::getRenderData()->lights;
    for (int i = 0; i < light->size(); i += 2) {
        float x = light->at(i);
        float y = light->at(i + 1);
        if (x == body->pos.x && y == body->pos.y) {
           light->erase(light->begin() + i);
           light->erase(light->begin() + i);

        }
    }
}

void Bitcoin::render() {
    Renderer::drawQuad(body->pos, body->size, texture);
}

void Bitcoin::update(float deleteTime) {

}

void Bitcoin::onCollision() {

}



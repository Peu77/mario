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

    lightX = new float{spawnPosition.x};
    lightY = new float{spawnPosition.y};

    Renderer::getRenderData()->lights->push_back(lightX);
    Renderer::getRenderData()->lights->push_back(lightY);
}

Bitcoin::~Bitcoin() {
    auto light = Renderer::getRenderData()->lights;
    for (int i = 0; i < light->size(); i += 2) {
        auto x = light->at(i);
        auto y = light->at(i + 1);
        if (x == lightX && y == lightY) {
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



//
// Created by peu77 on 2/13/22.
//

#include "Platform.h"

Platform::Platform(glm::vec2 spawnPosition) {
    texture = getTexture("res/textures/platform.png");
    scale = {100, 100};
    body = new Body();
    body->tag = "platform";
    body->friction = {0.8f, 0.9f};
    body->dynamic = true;
    lastPosition = spawnPosition;
    body->pos = spawnPosition;
    body->size = scale;
}

void Platform::update(float deleteTime) {
    if (right) {
        if (offset < range) {
            offset++;
            body->vel.x = 90;
        } else
            right = false;

    } else {
        if (offset > 0) {
            offset--;
            body->vel.x = -90;
        }else
            right = true;
    }

    body->data = &right;
}

void Platform::render() {
    Renderer::drawQuad(body->pos, scale, texture);
}

void Platform::onCollision() {

}

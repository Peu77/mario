//
// Created by peu77 on 2/19/22.
//

#include "BackgroundObject.h"

#include <utility>

BackgroundObject::BackgroundObject(std::string texturePath, float in_width, float in_height, glm::vec2 spawnPosition) {
    this->textureWidth = in_width;
    this->textureHeight = in_height;
    this->texturePath = texturePath;
    texture = getTexture(std::move(texturePath));
    scale = {in_width, in_height};
    body = new Body();
    body->tag = "backgroundObject";
    body->dynamic = false;
    type = Type::BACKGROUND;
    body->friction = {0.8f, 0.9f};
    body->pos = spawnPosition;
    body->size = scale;
}

void BackgroundObject::render() {
    Renderer::drawQuad(body->pos, scale, texture);
}

void BackgroundObject::update(float deltaTime) {
    GameObject::update(deltaTime);
}

void BackgroundObject::onCollision() {

}

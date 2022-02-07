//
// Created by peu77 on 2/7/22.
//

#include "Brick.h"

Brick::Brick(b2World &world, glm::vec2 spawnPosition) {
    position = spawnPosition;

    scale = {100, 100};

    b2BodyDef b_def;
    b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    b_def.position.Set(position.x, position.y);
    b_def.type = b2_dynamicBody;
    b_def.fixedRotation = true;
    b_def.gravityScale = 0;
    body = world.CreateBody(&b_def);
}

Brick::~Brick() {

}

void Brick::update(float deleteTime) {
    position = {body->GetPosition().x, body->GetPosition().y};
}

void Brick::render() {
    Renderer::drawQuad(position, scale);
}

void Brick::onCollision(GameObject* object) {

}

//
// Created by peu77 on 2/7/22.
//

#include "Brick.h"



Brick::Brick(b2World &world, glm::vec2 spawnPosition) {
    texture = Texture::getTexture("res/textures/brick.png");
    position = {spawnPosition.x, spawnPosition.y};

    scale = {100, 100};

    b2BodyDef b_def;
    b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    b_def.position.Set(position.x / PIXEL_TO_M, position.y / PIXEL_TO_M );
    b_def.type = b2_dynamicBody;
    b_def.fixedRotation = true;
    b_def.gravityScale = 0.0f;
    body = world.CreateBody(&b_def);


    b2PolygonShape b_shape;
    b_shape.SetAsBox(scale.x / 2.f / PIXEL_TO_M, scale.y / 2.f / PIXEL_TO_M);
    body->CreateFixture(&b_shape, 0.0f);
}

Brick::~Brick() {

}

void Brick::update(float deleteTime) {
    position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};

}

void Brick::render() {
    Renderer::drawQuad(position, scale, texture);
}

void Brick::onCollision(GameObject* object) {

}

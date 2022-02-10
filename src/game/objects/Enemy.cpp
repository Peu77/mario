//
// Created by peu77 on 2/9/22.
//

#include "Enemy.h"

Enemy::Enemy(b2World &world, glm::vec2 spawnPosition) {
    texture = getTexture("res/textures/enemy.png");

    tag = "enemy";

    position = {spawnPosition.x, spawnPosition.y};

    scale = {100, 100};

    b2BodyDef b_def;
    b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    b_def.position.Set(position.x / PIXEL_TO_M, position.y / PIXEL_TO_M);
    b_def.type = b2_dynamicBody;
    b_def.fixedRotation = true;
    b_def.gravityScale = 2.0f;
    body = world.CreateBody(&b_def);

    b2PolygonShape b_shape;
    b_shape.SetAsBox(scale.x / 2.f / PIXEL_TO_M, scale.y / 2.f / PIXEL_TO_M);

    b2FixtureDef fixDef;
    fixDef.shape = &b_shape;
    fixDef.density = 1;
    fixDef.friction = 1.0;
    body->CreateFixture(&fixDef);
}

void Enemy::update(float deltaTime) {
    position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};
}

void Enemy::render() {
    Renderer::drawQuad(position, scale, texture);
}

void Enemy::onCollision(GameObject *object) {

}

void Enemy::flip() {

}
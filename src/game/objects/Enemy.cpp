//
// Created by peu77 on 2/9/22.
//

#include "Enemy.h"

Enemy::Enemy(glm::vec2 spawnPosition) {
    std::vector<Texture*> textures;
    textures.push_back(getTexture("res/textures/enemy.png"));
    textures.push_back(getTexture("res/textures/enemy1.png"));
    texture = getTexture("res/textures/enemy.png");

    animation = new Animation(textures);



    scale = {100, 100};
    body = new Body();
    body->tag = "enemy";
    body->friction = {0.6f, 0.9f};
    body->pos = spawnPosition;
    body->dynamic = true;
    body->size = scale;

}

void Enemy::update(float deltaTime) {
    body->vel.y -= GRAVITY;

    body->vel.x = velX;

    texture = animation->getNext(deltaTime);
    /*
    b2Vec2 vel = body->GetLinearVelocity();

    body->SetLinearVelocity(vel);
    position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};
     */
}

void Enemy::render() {
    Renderer::drawQuad(body->pos, scale, texture);
}

void Enemy::onCollision() {
    if (body->contact[1] != nullptr && !body->contact[1]->dynamic) {
        if(velX != -130)
            flip();
        velX = -130;
        body->contact[1] = nullptr;
    }
    if (body->contact[3] != nullptr && !body->contact[3]->dynamic) {
        if(velX != 130)
            flip();
        velX = 130;
        body->contact[3] = nullptr;
    }

    /*
    if(object->position.y > position.y - scale.y && object->tag == "brick"){
        flip();
    }
     */
}

void Enemy::flip() {
    faceRight = !faceRight;
    scale.x *= -1;
}
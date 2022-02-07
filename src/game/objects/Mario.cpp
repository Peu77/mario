//
// Created by peu77 on 2/7/22.
//

#include "Mario.h"

Mario::Mario(b2World &world, glm::vec2 spawnPosition, GLFWwindow* window): windowId(window) {
    texture = getTexture("res/textures/mario.png");
    position = {spawnPosition.x, spawnPosition.y};

    scale = {100, 100};

    b2BodyDef b_def;
    b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    b_def.position.Set(position.x / PIXEL_TO_M , position.y / PIXEL_TO_M );
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

Mario::~Mario() {

}

void Mario::update(float deleteTime) {
    movement(deleteTime);
    position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};
}

void Mario::render() {
    Renderer::drawQuad(position, scale, texture);
}

void Mario::onCollision(GameObject* object) {
    jumping = false;
}

void Mario::movement(float deltaTime) {
    b2Vec2 vel = body->GetLinearVelocity();
    if(glfwGetKey(windowId, GLFW_KEY_A) == GLFW_PRESS)
        vel.x = -speed;
    else  if(glfwGetKey(windowId, GLFW_KEY_D) == GLFW_PRESS)
        vel.x = speed;

    if(glfwGetKey(windowId, GLFW_KEY_SPACE) == GLFW_PRESS)
        jump(vel);

    body->SetLinearVelocity(vel);
}

void Mario::jump(b2Vec2 &vel) {
    if(!jumping){
        jumping = true;
        vel.y = jumpForce;
    }
}

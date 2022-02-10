//
// Created by peu77 on 2/7/22.
//

#include <memory>
#include "Mario.h"

Mario::Mario(b2World &world, glm::vec2 spawnPosition, GLFWwindow *window, std::vector<GameObject *> *gameObjects)
        : windowId(window) {
    objects = gameObjects;
    this->world = &world;
    textureIdle = getTexture("res/textures/mario.png");
    textureJump = getTexture("res/textures/mario-jump.png");
    runTextures[0] = getTexture("res/textures/mario-run0.png");
    runTextures[1] = getTexture("res/textures/mario-run1.png");
    runTextures[2] = getTexture("res/textures/mario-run2.png");
    position = {spawnPosition.x, spawnPosition.y};
    texture = textureIdle;

    tag = "mario";

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

Mario::~Mario() {

}

void Mario::update(float deleteTime) {
    movement(deleteTime);
    position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};

    bool both = glfwGetKey(windowId, GLFW_KEY_A) && glfwGetKey(windowId, GLFW_KEY_D);

    if (both) {
        texture = textureIdle;
    } else if ((glfwGetKey(windowId, GLFW_KEY_A) || glfwGetKey(windowId, GLFW_KEY_D)) && !jumping) {
        runAnimation(deleteTime);
    } else if (jumping)
        texture = textureJump;
    else {
        texture = textureIdle;
    }

    if (!both) {
        if (glfwGetKey(windowId, GLFW_KEY_A) && faceRight)
            flip();
        else if (glfwGetKey(windowId, GLFW_KEY_D) && !faceRight)
            flip();
    }

}

void Mario::render() {
    Renderer::drawQuad(position, scale, texture);
}

void Mario::onCollision(GameObject *object) {
    if (jumping) {
        jumping = false;
    }


    if (object->tag == "enemy") {
        int targetY = object->position.y;
        int marioY = position.y - scale.y;
        int normalY = position.y;
        bool b = targetY > marioY && targetY < normalY;
        if (b){
            object->shouldDelete = true;
            jumping = true;
            b2Vec2 vel = body->GetLinearVelocity();
            vel.y = 14;
            body->SetLinearVelocity(vel);
        }

    }


}

void Mario::movement(float deltaTime) {
    b2Vec2 vel = body->GetLinearVelocity();
    if (glfwGetKey(windowId, GLFW_KEY_A) && glfwGetKey(windowId, GLFW_KEY_D)) {

    } else {
        if (glfwGetKey(windowId, GLFW_KEY_A) == GLFW_PRESS)
            vel.x = -speed;
        else if (glfwGetKey(windowId, GLFW_KEY_D) == GLFW_PRESS)
            vel.x = speed;
    }


    if (glfwGetKey(windowId, GLFW_KEY_SPACE) == GLFW_PRESS)
        jump(vel);

    body->SetLinearVelocity(vel);
}

void Mario::jump(b2Vec2 &vel) {
    if (!jumping) {
        jumping = true;
        vel.y = jumpForce;
    }
}

void Mario::flip() {
    faceRight = !faceRight;
    scale.x *= -1;
}

void Mario::runAnimation(float deltaTime) {
    texture = runTextures[animationState];

    if (animationTime > 0)
        animationTime -= deltaTime;
    else {
        animationTime = animationSpeed;
        animationState++;
        if (animationState >= 3)
            animationState = 0;
    }
}

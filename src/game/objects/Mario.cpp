//
// Created by peu77 on 2/7/22.
//

#include <memory>
#include "Mario.h"


Mario::Mario(glm::vec2 spawnPosition, GLFWwindow *window)
        : windowId(window) {
    textureIdle = getTexture("res/textures/mario.png");
    textureJump = getTexture("res/textures/mario-jump.png");
    std::vector<Texture *> textures;
    textures.push_back(getTexture("res/textures/mario-run0.png"));
    textures.push_back(getTexture("res/textures/mario-run1.png"));
    textures.push_back(getTexture("res/textures/mario-run2.png"));
    animation = new Animation(textures);
    body = new Body();
    body->tag = "mario";
    scale = {100, 100};
    body->data = this;
    body->pos = spawnPosition;
    body->size = scale;
    body->dynamic = true;
    body->vel = {0, -70};
}

Mario::~Mario() {
    delete animation;
}

void Mario::update(float deleteTime) {
    body->vel.y -= GRAVITY;
    movement(deleteTime);
    bool both = glfwGetKey(windowId, GLFW_KEY_A) && glfwGetKey(windowId, GLFW_KEY_D);

    if (both) {
        texture = textureIdle;
    } else if ((glfwGetKey(windowId, GLFW_KEY_A) || glfwGetKey(windowId, GLFW_KEY_D)) && !jumping) {
        texture = animation->getNext(deleteTime);
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
    Renderer::drawQuad(body->pos, scale, texture);
    for (int i = 0; i < 4; i++) {
        /*
        if (body->contact[i]){
            Renderer::drawQuad(body->contact[i]->pos, body->contact[i]->size);
        }
         */
        body->contact[i] = nullptr;
    }
}

void Mario::onCollision() {
    if (body->contact[0] != nullptr) {
        if (jumping) {
            jumping = false;
        }
        if (body->contact[0]->tag == "enemy")
            body->vel.y = jumpForce / 2;
    }
}

void Mario::movement(float deltaTime) {
    if (glfwGetKey(windowId, GLFW_KEY_A) && glfwGetKey(windowId, GLFW_KEY_D)) {

    } else {
        if (glfwGetKey(windowId, GLFW_KEY_A) == GLFW_PRESS)
            body->vel.x = -speed;
        else if (glfwGetKey(windowId, GLFW_KEY_D) == GLFW_PRESS)

            body->vel.x = speed;
    }


    if (glfwGetKey(windowId, GLFW_KEY_SPACE) == GLFW_PRESS)
        jump();


}

void Mario::jump() {
    if (!jumping) {
        jumping = true;
        body->vel.y = jumpForce;
    }
}

void Mario::flip() {
    faceRight = !faceRight;
    scale.x *= -1;
}

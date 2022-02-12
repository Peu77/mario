//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_H
#define MARIO_H

#include "GameObject.h"
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "Enemy.h"
#include "../Animation.h"


class Mario : public GameObject {
public:
    Mario(glm::vec2 spawnPosition, GLFWwindow* window);

    ~Mario();

    void update(float deltaTime) override;

    void render() override;

    void onCollision() override;

private:
    Animation* animation;
    void movement(float deltaTime);
    void jump();
    void flip();

private:
    GLFWwindow* windowId;
    bool faceRight = true;
    bool jumping = false;
    float jumpForce = 1440;
    float speed = 500.0f;
    Texture* texture;
    Texture* textureJump;
    Texture* textureIdle;
    std::vector<GameObject*> *objects;
};


#endif //MARIO_BRICK_H

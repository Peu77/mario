//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_H
#define MARIO_H

#include "GameObject.h"
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"

class Mario : public GameObject {
public:
    Mario(b2World &world, glm::vec2 spawnPosition, GLFWwindow* window);

    ~Mario();

    void update(float deltaTime) override;

    void render() override;

    void onCollision(GameObject *object) override;

private:
    void movement(float deltaTime);
    void jump(b2Vec2& vel);

private:
    GLFWwindow* windowId;
    b2Body *body;
    bool jumping = false;
    float jumpForce = 17;
    float speed = 5.0f;
    Texture* texture;
};


#endif //MARIO_BRICK_H

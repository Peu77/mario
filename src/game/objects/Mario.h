//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_H
#define MARIO_H

#include "GameObject.h"
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "Enemy.h"


class Mario : public GameObject {
public:
    Mario(b2World &world, glm::vec2 spawnPosition, GLFWwindow* window, std::vector<GameObject*> *gameObjects);

    ~Mario();

    void update(float deltaTime) override;

    void render() override;

    void onCollision(GameObject *object) override;

private:
    void movement(float deltaTime);
    void jump(b2Vec2& vel);
    void flip();
    void runAnimation(float deltaTime);

private:
    GLFWwindow* windowId;
    b2World* world;
    bool faceRight = true;
    bool jumping = false;
    float jumpForce = 17;
    int animationState = 0;
    float animationSpeed = 0.1f;
    float animationTime = animationSpeed;
    float speed = 5.0f;
    Texture* texture;
    Texture* textureJump;
    Texture* textureIdle;
    Texture* runTextures[3];
    std::vector<GameObject*> *objects;
};


#endif //MARIO_BRICK_H

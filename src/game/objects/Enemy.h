//
// Created by peu77 on 2/9/22.
//

#ifndef MARIO_ENEMY_H
#define MARIO_ENEMY_H

#include "GameObject.h"
#include "../Animation.h"
#include "Mario.h"

class Enemy : public GameObject {
public:
    Enemy(glm::vec2 spawnPosition);

    void update(float deltaTime) override;

    void render() override;

    void onCollision() override;

private:
    void flip();

private:
    bool faceRight = true;
    float velX = 130;
    Animation* animation;
    Texture* texture;
};


#endif //MARIO_ENEMY_H

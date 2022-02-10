//
// Created by peu77 on 2/9/22.
//

#ifndef MARIO_ENEMY_H
#define MARIO_ENEMY_H

#include "GameObject.h"


class Enemy : public GameObject {
public:
    Enemy(b2World &world, glm::vec2 spawnPosition);

    void update(float deltaTime) override;

    void render() override;

    void onCollision(GameObject *object) override;

private:
    void flip();

private:
    bool faceRight = true;
    Texture* texture;
};


#endif //MARIO_ENEMY_H

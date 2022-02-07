//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_BRICK_H
#define MARIO_BRICK_H

#include "GameObject.h"

class Brick : GameObject {
public:
    Brick(b2World &world, glm::vec2 spawnPosition);

    ~Brick();

    void update(float deleteTime) override;

    void render() override;

    void onCollision(GameObject* object) override;

private:
    b2Body* body;
};


#endif //MARIO_BRICK_H

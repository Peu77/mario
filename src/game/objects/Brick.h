//
// Created by peu77 on 2/7/22.
//

#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class Brick : public GameObject {
public:
    Brick(b2World &world, glm::vec2 spawnPosition);

    ~Brick();

    void update(float deleteTime) override;

    void render() override;

    void onCollision(GameObject* object) override;

private:
    b2Body* body;
    Texture* texture;

    float tile_count = 200;
    float tile_width = 100;
};


#endif

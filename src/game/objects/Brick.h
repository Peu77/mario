//
// Created by peu77 on 2/7/22.
//

#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class Brick : public GameObject {
public:
    Brick(glm::vec2 spawnPosition, float tiles);

    ~Brick();

    void update(float deleteTime) override;

    void render() override;

    void onCollision() override;

private:
    //b2Body* body;
    Texture* texture;

    float tile_count;
};


#endif

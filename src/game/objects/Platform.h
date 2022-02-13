//
// Created by peu77 on 2/13/22.
//

#ifndef MARIO_PLATFORM_H
#define MARIO_PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject {
public:
    Platform(glm::vec2 spawnPosition);

    void update(float deleteTime) override;

    void render() override;

    void onCollision() override;

private:
    Texture *texture;
    glm::vec2 lastPosition;
    float offset = 0;
    float range = 100*3;
    bool right = true;
};


#endif //MARIO_PLATFORM_H

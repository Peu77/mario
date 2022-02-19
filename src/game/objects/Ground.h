//
// Created by peu77 on 2/18/22.
//

#ifndef MARIO_GROUND_H
#define MARIO_GROUND_H

#include "GameObject.h"

class Ground : public GameObject {
public:
    Ground(glm::vec2 spawnPosition);

    void update(float deleteTime) override;

    void render() override;

    void onCollision() override;


private:
    Texture *texture;
};


#endif //MARIO_GROUND_H

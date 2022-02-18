//
// Created by peu77 on 2/17/22.
//

#ifndef MARIO_BITCOIN_H
#define MARIO_BITCOIN_H

#include "GameObject.h"

class Bitcoin : public GameObject {

public:
    Bitcoin(glm::vec2 spawnPosition);

    ~Bitcoin() override;

    void update(float deleteTime) override;

    void render() override;

    void onCollision() override;


private:
    Texture *texture;
};


#endif //MARIO_BITCOIN_H

//
// Created by peu77 on 2/14/22.
//

#ifndef MARIO_CHECKPOINT_H
#define MARIO_CHECKPOINT_H

#include "GameObject.h"
#include "particle/ParticleHandler.h"



class Checkpoint : public GameObject {


private:
    Texture *texture;
    Texture *particle1;
    Texture *particle2;
    Texture *particle;
    ParticleHandler *particleHandler;

public:
    Checkpoint(glm::vec2 spawnPosition);

    ~Checkpoint();

    void update(float deleteTime) override;

    void render() override;

    void onCollision() override;

    void active();
};


#endif //MARIO_CHECKPOINT_H

//
// Created by peu77 on 2/19/22.
//

#ifndef MARIO_FIREBALL_H
#define MARIO_FIREBALL_H

#include "GameObject.h"

class Fireball : public GameObject {
public:
    Fireball(glm::vec2 spawnPosition, glm::vec2 velocity, GameObject* shooter);

    void update(float deleteTime) override;

    void render() override;

    void onCollision() override;

private:
    Texture *texture;
    GameObject* shooter;
};


#endif //MARIO_FIREBALL_H

//
// Created by peu77 on 2/19/22.
//

#ifndef MARIO_BACKGROUNDOBJECT_H
#define MARIO_BACKGROUNDOBJECT_H

#include "GameObject.h"

class BackgroundObject : public GameObject {
public:
    BackgroundObject(std::string texturePath, float in_width, float in_height, glm::vec2 spawnPosition);

    void render() override;

    void update(float deltaTime) override;

    void onCollision() override;

private:
    Texture *texture;
};


#endif //MARIO_BACKGROUNDOBJECT_H

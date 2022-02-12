//
// Created by peu77 on 2/12/22.
//

#ifndef MARIO_ANIMATION_H
#define MARIO_ANIMATION_H

#include "vector"
#include "texture/Texture.h"

class Animation {
private:
    std::vector<Texture *> textures;
    int animationState = 0;
    float animationSpeed = 0.1f;
    float animationTime = animationSpeed;

public:
    Animation(std::vector<Texture *> in_textures);

    Texture *getNext(float deltaTime);


};


#endif //MARIO_ANIMATION_H

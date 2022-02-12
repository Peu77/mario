//
// Created by peu77 on 2/12/22.
//

#include "Animation.h"

#include <utility>

Animation::Animation(std::vector<Texture *> in_textures) {
    textures = std::move(in_textures);
}

Texture *Animation::getNext(float deltaTime) {
    auto texture = textures[animationState];

    if (animationTime > 0)
        animationTime -= deltaTime;
    else {
        animationTime = animationSpeed;
        animationState++;
        if (animationState >= textures.size())
            animationState = 0;
    }

    return texture;
}

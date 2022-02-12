//
// Created by peu77 on 2/10/22.
//

#ifndef MARIO_BODY_H
#define MARIO_BODY_H

#include "../GlmInclude.h"
#include "iostream"


struct Body {
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 vel;
    Body* contact[4];
    void* data;
    bool dynamic = false;
};


#endif //MARIO_BODY_H

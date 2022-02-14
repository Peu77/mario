//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_CAMERA_H
#define MARIO_CAMERA_H

#include "../GlmInclude.h"


class Camera {
public:
    glm::mat4 view{};
    glm::mat4 proj{};
    glm::vec2 position{};

    Camera(int width, int height);

    void updateProj(int &width, int &height);

    void updateView();
};


#endif //MARIO_CAMERA_H

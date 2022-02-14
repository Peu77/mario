//
// Created by peu77 on 2/7/22.
//

#include "Camera.h"

Camera::Camera(int width, int height) {
    position = glm::vec2(0);
    updateProj(width, height);
    view = glm::mat4(1);
}


void Camera::updateProj(int &width, int &height) {
    proj = glm::ortho(0.0f, (float) width, 0.0f, (float) height, 0.0f, 1.0f);
}

void Camera::updateView() {
    view = glm::translate(glm::mat4(1), {position.x, position.y, 0.0f});
    view = glm::inverse(view);
}


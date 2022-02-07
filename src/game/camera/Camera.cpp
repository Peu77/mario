//
// Created by peu77 on 2/7/22.
//

#include "Camera.h"

Camera::Camera(int width, int height) {
    position = glm::vec2(0);
    proj = glm::ortho(0.0f, (float) width, 0.0f, (float) height, 0.0f, 1.0f);
    view = glm::mat4(1);
}

void Camera::updateView() {
    view = glm::translate(view, {position.x, position.y, 0.0f});
}
//
// Created by peu77 on 2/12/22.
//

#ifndef MARIO_SCREENEDITOR_H
#define MARIO_SCREENEDITOR_H


#include "../../window/Screen.h"
#include "../physic/World.h"
#include "../camera/Camera.h"
#include "../objects/Brick.h"


class ScreenEditor : public Screen {
private:
    World *world;
    int width, height;
    bool moving = false;
    glm::vec2 offset = {0.0, 0.0};
    glm::vec2 last = {0.0, 0.0};

public:
    ScreenEditor(int& in_width, int& in_height);

    ~ScreenEditor();

    glm::vec2 getPosition(int& mouseX, int& mouseY) const;

    GameObject* getGameObject(int& mouseX, int& mouseY);

    void draw(int &mouseX, int &mouseY) override;

    void onClick(int &mouseX, int &mouseY, int& button) override;

    void onRelease(int &mouseX, int &mouseY, int& button) override;

    void update(int &mouseX, int &mouseY, float deltaTime) override;
};


#endif //MARIO_SCREENEDITOR_H

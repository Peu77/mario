//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_GAME_H
#define MARIO_GAME_H

#include "../window/Window.h"
#include "renderer/Renderer.h"
#include "camera/Camera.h"
#include "vector"

#include "objects/Brick.h"
#include "objects/Enemy.h"
#include "objects/Mario.h"


class Game {
private:
    Window *window;
    Camera *camera;
    b2World *physicsWorld;
    Mario *mario;
    std::vector<GameObject *> objects;

    void removeObject(GameObject &object) {
        for (int i = 0; i < objects.size(); i++)
            if (objects.at(i) == &object)
                objects.erase(objects.begin() + i);
    }

public:
    Game();

    ~Game();

private:
    void init();

    void update(float delta);

    void render();

    void runTick();
};


#endif //MARIO_GAME_H

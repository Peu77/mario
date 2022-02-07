//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_GAME_H
#define MARIO_GAME_H

#include "../window/Window.h"
#include "renderer/Renderer.h"
#include "camera/Camera.h"
#include "Box2dInclude.h"
#include "vector"
#include "objects/GameObject.h"
class Game {
private:
    std::vector<GameObject*> objects;
    Window *window;
    Camera* camera;
    b2World* physicsWorld;

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

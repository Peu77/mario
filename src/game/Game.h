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

#include "../window/Screen.h"
#include "screens/ScreenMain.h"

static Screen *screen;

class Game {
private:
    Window *window;
    Camera *camera;
    Mario *mario;

public:
    Game();

    ~Game();

private:
    void init();

    void updateWorld(float delta);

    void update(int &mouseX, int &mouseY, float delta);

    void renderWorld();

    static void onMouseClick(GLFWwindow *window, int button, int action, int mods);

    static glm::vec2 getMousePosition(GLFWwindow *window);

    void render(int &mouseX, int &mouseY);

    void runTick();
};


#endif //MARIO_GAME_H

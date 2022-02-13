//
// Created by peu77 on 2/7/22.
//

#include <ctime>
#include <chrono>

#include "Game.h"
#include "physic/World.h"

static int width = 1300;
static int height = 1100;

World *world;

Game::Game() {

    this->init();
    this->window = new Window("mario", width, height);


    glViewport(0, 0, width, height);

    Renderer::init(width, height, window->WindowId);

    screen = new ScreenMain([](Screen *in_screen) {
        screen = in_screen;
    }, width, height);

    glfwSetMouseButtonCallback(window->WindowId, onMouseClick);
    glfwSetKeyCallback(window->WindowId, [](GLFWwindow *id, int key, int scancode, int action, int mods) {
        if (mods == GLFW_RELEASE && key == GLFW_KEY_ESCAPE) {
            screen = new ScreenMain([](Screen *in_screen) {
                screen = in_screen;
            }, width, height);
        }

    });

    world = new World(width, height);
    for (int i = 0; i < 10; ++i) {
        {
            auto brick = new Brick({100 * i, 20});
            world->registerBody(brick);
        }
    }

    for (int i = 0; i < 10; ++i) {
        {
            auto brick = new Brick({100 * 10, 20 + i * 100});
            world->registerBody(brick);
        }
    }

    {
        auto brick = new Brick({600, 120});
        world->registerBody(brick);
    }


    auto *enemy = new Enemy({600, 300});
    world->registerBody(enemy);
    auto mario = new Mario({300, 700}, window->WindowId);
    world->registerBody(mario);
    this->runTick();
}

Game::~Game() {
    Renderer::shutdown();
    std::cout << "shutdown game" << std::endl;
}

void Game::init() {
    if (!glfwInit())
        std::cout << "glfw is not init" << std::endl;
}

void Game::onMouseClick(GLFWwindow *window, int button, int action, int mods) {
    if (screen != nullptr) {

        glm::vec2 mousePos = getMousePosition(window);

        int mouseX = (int) mousePos.x;
        int mouseY = (int) mousePos.y;

        switch (action) {
            case GLFW_PRESS:
                screen->onClick(mouseX, mouseY, button);
                break;
            case GLFW_RELEASE:
                screen->onRelease(mouseX, mouseY, button);
                break;
        }
    }
}

void Game::updateWorld(float delta) {
    world->step(delta);

}

void Game::update(int &mouseX, int &mouseY, float delta) {
    if (screen == nullptr)
        updateWorld(delta);
    else
        screen->update(mouseX, mouseY, delta);
}

void Game::renderWorld() {
    world->renderObjects();
}

void Game::render(int &mouseX, int &mouseY) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (screen == nullptr)
        renderWorld();
    else {
        Renderer::beginScene(*Renderer::getRenderData()->menuCamera);
        screen->draw(mouseX, mouseY);
    }
}

void Game::runTick() {

    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window->WindowId)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        auto deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;


        glm::vec2 mousePos = getMousePosition(window->WindowId);
        int mouseX = (int) mousePos.x;
        int mouseY = (int) mousePos.y;
        update(mouseX, mouseY, deltaTime);
        render(mouseX, mouseY);

        glfwSwapBuffers(window->WindowId);
        glfwPollEvents();
    }
}

glm::vec2 Game::getMousePosition(GLFWwindow *window) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int realMouseY = height - (int) mouseY;
    //std::cout << "mouseX: " << realMouseY << " mouseY: " << realMouseY << std::endl;
    return {mouseX, realMouseY};
}





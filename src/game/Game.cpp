//
// Created by peu77 on 2/7/22.
//

#include "Game.h"

Game::Game() {
    int width = 900;
    int height = 700;

    this->init();
    this->window = new Window("mario", width, height);

    glViewport(0,0, width, height);
    camera = new Camera(width, height);

    b2Vec2 gravity(0, -20);
    this->physicsWorld = new b2World(gravity);

    Renderer::init();
    Renderer::beginScene(*camera);
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

void Game::update(float delta) {
    physicsWorld->Step(delta, 8, 3);
}

void Game::render() {

    Renderer::drawQuad({0, 0}, {100, 100});
}

void Game::runTick() {

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window->WindowId)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        double currentTime = glfwGetTime();
        auto deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;

        update(deltaTime);
        render();

        glfwSwapBuffers(window->WindowId);
        glfwPollEvents();
    }
}



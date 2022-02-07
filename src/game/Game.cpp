//
// Created by peu77 on 2/7/22.
//

#include "Game.h"
#include "objects/Brick.h"
#include "objects/Mario.h"
#include "collisionListener/CollisionListener.h"

Game::Game() {
    int width = 1300;
    int height = 1100;

    this->init();
    this->window = new Window("mario", width, height);

    glViewport(0, 0, width, height);
    camera = new Camera(width, height);

    b2Vec2 gravity(0, -20.0);
    this->physicsWorld = new b2World(gravity);



    for (int i = 0; i < 10; ++i) {
        auto brick = new Brick(*physicsWorld, {100 * i, 50});
        objects.push_back(brick);
    }

    auto mario = new Mario(*physicsWorld, {300, 300}, window->WindowId);

    objects.push_back(mario);


    CollisionListener collisionListener(*physicsWorld);

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

    for (const auto &item: objects)
        item->update(delta);
}

void Game::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (const auto &item: objects)
        item->render();
}

void Game::runTick() {

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window->WindowId)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT );


        double currentTime = glfwGetTime();
        auto deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;

        update(deltaTime);
        render();

        glfwSwapBuffers(window->WindowId);
        glfwPollEvents();
    }
}



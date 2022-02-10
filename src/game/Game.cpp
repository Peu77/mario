//
// Created by peu77 on 2/7/22.
//

#include <ctime>

#include "objects/Brick.h"
#include "collisionListener/CollisionListener.h"
#include "Game.h"
#include "renderer/font.h"

int width = 1300;
int height = 1100;

Font* font;

Game::Game() {

    this->init();
    this->window = new Window("mario", width, height);


    glViewport(0, 0, width, height);
    camera = new Camera(width, height);

    Shader vertex("res/shaders/font.vertex", GL_VERTEX_SHADER);
    Shader fragment("res/shaders/font.fragment", GL_FRAGMENT_SHADER);
    Program fontProgram(&vertex, &fragment);
    font = new Font(camera->proj, &fontProgram);

    b2Vec2 gravity(0, -20.0);
    this->physicsWorld = new b2World(gravity);

    auto brick = new Brick(*physicsWorld, {0, 0});
    objects.push_back(brick);

    auto* enemy = new Enemy(*physicsWorld, {600, 300});
    objects.push_back(enemy);
    mario = new Mario(*physicsWorld, {300, 300}, window->WindowId, &objects);
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

    camera->position = {mario->position.x - (width / 2.0f), camera->position.y};
    camera->updateView();

    for (const auto &item : this->objects)
        if(item->shouldDelete){
            physicsWorld->DestroyBody(item->body);
            this->removeObject(*item);
        }
}

void Game::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Renderer::beginScene(*camera);

    font->RenderText(
            "test",
            100, 400, 1, {1.0f, 0.0f, 0.0f}
            );
    for (const auto &item: objects)
        item->render();
}

void Game::runTick() {

    double lastTime = glfwGetTime();


    while (!glfwWindowShouldClose(window->WindowId)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        auto deltaTime = float(currentTime - lastTime);

        lastTime = currentTime;
        update(deltaTime);
        render();

        glfwSwapBuffers(window->WindowId);
        glfwPollEvents();
    }
}



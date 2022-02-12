//
// Created by peu77 on 2/7/22.
//

#include <ctime>
#include <chrono>

#include "Game.h"
#include "renderer/font.h"
#include "physic/World.h"

int width = 1300;
int height = 1100;

Font* font;
World* world;

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
    world = new World();
    for (int i = 0; i < 10; ++i) {
        {
            auto brick = new Brick(*physicsWorld, {100 * i, 20}, 10);
            world->registerBody(brick->body);
            objects.push_back(brick);
        }
    }

    {
        auto brick = new Brick(*physicsWorld, {600, 120}, 10);
        world->registerBody(brick->body);
        objects.push_back(brick);
    }


    auto* enemy = new Enemy(*physicsWorld, {600, 300});
    world->registerBody(enemy->body);
    objects.push_back(enemy);
    mario = new Mario(*physicsWorld, {300, 700}, window->WindowId, &objects);
    world->registerBody(mario->body);
    objects.push_back(mario);

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

    world->step(delta);

    for (const auto &item: objects)
        item->update(delta);

    camera->position = {mario->body->pos.x - (width / 2.0f), camera->position.y};
    camera->updateView();

    for (const auto &item : this->objects)
        if(item->shouldDelete){
          //  physicsWorld->DestroyBody(item->body);
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
    /*
    auto m_tp1 = std::chrono::system_clock::now();
    auto m_tp2 = std::chrono::system_clock::now();
    float		fFrameTimer = 1.0f;
    int			nFrameCount = 0;
    uint32_t	nLastFPS = 0;
     */

    while (!glfwWindowShouldClose(window->WindowId)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        auto deltaTime = float(currentTime - lastTime);
      //  m_tp2 = std::chrono::system_clock::now();
       // std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
        //m_tp1 = m_tp2;
        //float fElapsedTime = elapsedTime.count();
        lastTime = currentTime;
        update(deltaTime);
        render();

        /*
        fFrameTimer += fElapsedTime;
        nFrameCount++;

        if (fFrameTimer >= 1.0f)
        {
            nLastFPS = nFrameCount;
            fFrameTimer -= 1.0f;
            std::string sTitle = "FPS: " + std::to_string(nFrameCount);
            std::cout << sTitle << std::endl;
            //glfwSetWindowTitle(window->WindowId, sTitle.c_str());
            nFrameCount = 0;
        }
         */

        glfwSwapBuffers(window->WindowId);
        glfwPollEvents();
    }
}



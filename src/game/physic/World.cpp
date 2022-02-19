//
// Created by peu77 on 2/10/22.
//

#include "World.h"

void World::registerBody(GameObject *body) {
    bodies.push_back(body);
}


void World::renderObjects() {
    Renderer::beginScene(*camera);

    for (const auto &item: bodies) {
        if (item->type == Type::BACKGROUND)
            if (item->body->pos.x < camera->position.x + width + 200 &&
                item->body->pos.x > camera->position.x - width / 2) // only render when see
                item->render();
    }


    for (const auto &item: bodies) {
        if (item->type == Type::FOREGROUND)
            if (item->body->pos.x < camera->position.x + width + 200 &&
                item->body->pos.x > camera->position.x - width / 2) // only render when see
                item->render();
    }

}

void World::step(float deltaTime, int &width, int &height) {

    float lerp = 0.7f;
    if (mario != nullptr) {
        camera->position.x += (mario->body->pos.x - width / 2 - camera->position.x) * lerp * deltaTime;
        camera->position.y += (mario->body->pos.y - height / 2 - camera->position.y) * lerp * deltaTime;
        camera->position.x = std::max(camera->position.x, 0.0f);
        camera->position.y = std::max(camera->position.y, 0.0f);
        camera->updateView();
    }


    for (const auto &item: bodies) {
        if (item->body->dynamic && item->type == Type::FOREGROUND) {
            glm::vec2 cp, cn;
            float t = 0, min_t = INFINITY;
            std::vector<std::pair<int, float>> z;
            for (size_t i = 0; i < bodies.size(); i++) {
                auto target = bodies[i];
                if (target != item && target->type == Type::FOREGROUND) // && !target->body->dynamic
                    if (DynamicRectVsRect(item->body, deltaTime, *target->body, cp, cn, t)) {
                        z.push_back({i, t});
                    }
            }

            std::sort(z.begin(), z.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
                return a.second < b.second;
            });

            for (auto j: z)
                if (ResolveDynamicRectVsRect(item->body, deltaTime, bodies[j.first]->body)) {
                    item->onCollision();
                    glm::vec2 friction = bodies[j.first]->body->friction;

                    item->body->vel.x = friction.x * item->body->vel.x;
                    if (item->body->vel.y < 0)
                        item->body->vel.y = friction.y * item->body->vel.y;
                }

            //item->body->pos += item->body->vel * deltaTime;
            float x = item->body->vel.x;
            item->body->pos.x = item->getVelocityX(x, item->body->pos.x, deltaTime);
            item->body->pos.y += item->body->vel.y * deltaTime;
        }

        item->update(deltaTime);
        if (item->shouldDelete)
            this->removeObject(*item);
    }

    //   camera->position = {mario->body->pos.x - (width / 2.0f), camera->position.y};
    //  camera->updateView();



}

World::~World() {
    std::cout << "delete world" << std::endl;
    bodies.clear();
}

World::World(int &in_width, int &in_height) : width(in_width), height(in_height) {
    camera = new Camera(in_width, in_height);
}


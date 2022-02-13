//
// Created by peu77 on 2/10/22.
//

#include "World.h"

void World::registerBody(GameObject *body) {
    bodies.push_back(body);
}


void World::renderObjects() {
    Renderer::beginScene(*camera);

    for (const auto &item: bodies)
        item->render();
}

void World::step(float deltaTime) {
    for (const auto &item: bodies) {
        if (item->body->dynamic) {
            glm::vec2 cp, cn;
            float t = 0, min_t = INFINITY;
            std::vector<std::pair<int, float>> z;
            for (size_t i = 0; i < bodies.size(); i++) {
                auto target = bodies[i];
                if (target != item) // && !target->body->dynamic
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
                    item->body->vel.y = friction.y * item->body->vel.y;
                }

            item->body->pos += item->body->vel * deltaTime;
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

World::World(int &in_width, int &in_height) {
    camera = new Camera(in_width, in_height);
}


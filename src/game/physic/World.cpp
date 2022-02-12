//
// Created by peu77 on 2/10/22.
//

#include "World.h"

void World::registerBody(Body *body) {
    bodies.push_back(body);
}

void World::step(float deltaTime) {
    for (const auto &item: bodies) {
        if (item->dynamic) {
            /*
            for (const auto &staticItem: bodies)
                if (staticItem != item)
                    if(ResolveDynamicRectVsRect(item, deltaTime, staticItem)){
                        auto gameObject = (GameObject*) item->data;
                        gameObject->onCollision();
                    }
                    */
            glm::vec2 cp, cn;
            float t = 0, min_t = INFINITY;
            std::vector<std::pair<int, float>> z;
            for (size_t i = 0; i < bodies.size(); i++) {
                auto target = bodies[i];
                if (target != item)
                    if (DynamicRectVsRect(item, deltaTime, *target, cp, cn, t)) {
                        z.push_back({i, t});
                    }
            }

            std::sort(z.begin(), z.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
                return a.second < b.second;
            });

            for (auto j: z)
                if (ResolveDynamicRectVsRect(item, deltaTime, bodies[j.first])) {
                    auto gameObject = (GameObject *) item->data;
                    gameObject->onCollision();
                }

            item->pos += item->vel * deltaTime;
        }

    }

}

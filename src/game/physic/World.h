//
// Created by peu77 on 2/10/22.
//

#ifndef MARIO_WORLD_H
#define MARIO_WORLD_H

#include "vector"
#include "../objects/GameObject.h"
#include "../objects/Mario.h"
#include "../camera/Camera.h"
#include "../objects/Brick.h"
#include "../objects/Platform.h"
#include "../objects/Checkpoint.h"
#include "../objects/Bitcoin.h"
#include "iostream"
#include "fstream"
#include "json/json.h"


class World {
public:
    Camera *camera;
    Mario *mario;
    int &width, height;

    std::vector<GameObject *> bodies;

    void registerBody(GameObject *body);

    void step(float deltaTime, int &width, int &height);

    void renderObjects();

    void removeObject(GameObject &object) {
        for (int i = 0; i < bodies.size(); i++)
            if (bodies.at(i) == &object) {
                delete bodies.at(i);
                bodies.erase(bodies.begin() + i);


            }
    }

    void removeObject(Body &object) {
        for (int i = 0; i < bodies.size(); i++)
            if (bodies.at(i)->body == &object){
                auto d = bodies.at(i);
                delete &d;
                bodies.erase(bodies.begin() + i);

            }

    }

    World(int &in_width, int &in_height);

    ~World();

    GameObject *genObject(const std::string &tag, int &x, int &y) {
        GameObject *object = nullptr;

        if (tag == "brick")
            object = new Brick({x, y});
        else if (tag == "mario") {
            object = new Mario({x, y});
            mario = (Mario *) object;
        } else if (tag == "enemy") {
            object = new Enemy({x, y});
        } else if (tag == "platform") {
            object = new Platform({x, y});
        } else if (tag == "checkpoint") {
            object = new Checkpoint({x, y});
        } else if (tag == "bitcoin") {
            object = new Bitcoin({x, y});
        }

        return object;
    }

    void load() {
        Renderer::getRenderData()->lights->clear();

        Json::Value root;
        Json::Reader reader;
        std::ifstream stream("map.json");

        if (!stream.good()) {
            std::cout << "file not exist" << std::endl;
            return;
        }
        std::string line;
        std::string json;
        while (getline(stream, line)) {
            json += line + "\n";
        }
        stream.close();

        bool success = reader.parse(json, root, false);

        if (success) {
            int amount = root["amount"].asInt();
            for (int i = 0; i < amount; ++i) {
                std::string index = std::to_string(i);
                std::string tag = root[index]["tag"].asString();
                int x = root[index]["x"].asInt();
                int y = root[index]["y"].asInt();
                auto object = genObject(tag, x, y);
                if (object == nullptr)
                    std::cout << "cannot find tag " << tag << std::endl;
                else
                    bodies.push_back(object);
            }
        }
    }


    void save() {
        Json::Value root;
        root["amount"] = bodies.size();
        for (int i = 0; i < bodies.size(); ++i) {
            auto body = bodies.at(i);
            root[std::to_string(i)]["tag"] = body->body->tag;
            root[std::to_string(i)]["x"] = body->body->pos.x;
            root[std::to_string(i)]["y"] = body->body->pos.y;
        }

        Json::StyledWriter styledWriter;

        std::string json = styledWriter.write(root);
        std::cout << "write: " << json << std::endl;
        std::ofstream file;
        file.open("map.json");
        file << json;
        file.close();
    }

    static bool PointVsRect(const glm::vec2 &p, const Body *r) {
        return (p.x >= r->pos.x && p.y >= r->pos.y && p.x < r->pos.x + r->size.x && p.y < r->pos.y + r->size.y);
    }

    static bool RectVsRect(const Body *r1, const Body *r2) {
        return (r1->pos.x < r2->pos.x + r2->size.x && r1->pos.x + r1->size.x > r2->pos.x &&
                r1->pos.y < r2->pos.y + r2->size.y && r1->pos.y + r1->size.y > r2->pos.y);
    }

    static bool
    RayVsRect(const glm::vec2 &ray_origin, const glm::vec2 &ray_dir, const Body *target, glm::vec2 &contact_point,
              glm::vec2 &contact_normal, float &t_hit_near) {
        contact_normal = {0, 0};
        contact_point = {0, 0};

        // Cache division
        glm::vec invdir = 1.0f / ray_dir;

        // Calculate intersections with rectangle bounding axes
        glm::vec t_near = (target->pos - ray_origin) * invdir;
        glm::vec t_far = (target->pos + target->size - ray_origin) * invdir;

        if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
        if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

        // Sort distances
        if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
        if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

        // Early rejection
        if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

        // Closest 'time' will be the first contact
        t_hit_near = std::max(t_near.x, t_near.y);

        // Furthest 'time' is contact on opposite side of target
        float t_hit_far = std::min(t_far.x, t_far.y);

        // Reject if ray direction is pointing away from object
        if (t_hit_far < 0)
            return false;

        // Contact point of collision from parametric line equation
        contact_point = ray_origin + t_hit_near * ray_dir;

        if (t_near.x > t_near.y)
            if (invdir.x < 0)
                contact_normal = {1, 0};
            else
                contact_normal = {-1, 0};
        else if (t_near.x < t_near.y)
            if (invdir.y < 0)
                contact_normal = {0, 1};
            else
                contact_normal = {0, -1};

        // Note if t_near == t_far, collision is principly in a diagonal
        // so pointless to resolve. By returning a CN={0,0} even though its
        // considered a hit, the resolver wont change anything.
        return true;
    }

    static bool DynamicRectVsRect(const Body *r_dynamic, const float fTimeStep, const Body &r_static,
                                  glm::vec2 &contact_point, glm::vec2 &contact_normal, float &contact_time) {
        // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start

        if (r_dynamic->vel.x == 0 && r_dynamic->vel.y == 0)
            return false;

        // Expand target rectangle by source dimensions
        Body expanded_target;
        expanded_target.pos = r_static.pos - r_dynamic->size / 2.0f;
        expanded_target.size = r_static.size + r_dynamic->size;

        if (RayVsRect(r_dynamic->pos + r_dynamic->size / 2.0f, r_dynamic->vel * fTimeStep, &expanded_target,
                      contact_point, contact_normal, contact_time)) {
            return (contact_time >= 0.0f && contact_time < 1.0f);
        } else
            return false;
    }


    static bool ResolveDynamicRectVsRect(Body *r_dynamic, const float fTimeStep, Body *r_static) {
        glm::vec2 contact_point, contact_normal;
        float contact_time = 0.0f;
        if (DynamicRectVsRect(r_dynamic, fTimeStep, *r_static, contact_point, contact_normal, contact_time)) {
            if (contact_normal.y > 0) r_dynamic->contact[0] = r_static; else nullptr;
            if (contact_normal.x < 0) r_dynamic->contact[1] = r_static; else nullptr;
            if (contact_normal.y < 0) r_dynamic->contact[2] = r_static; else nullptr;
            if (contact_normal.x > 0) r_dynamic->contact[3] = r_static; else nullptr;

            if (r_static->canCollide)
                r_dynamic->vel += contact_normal * glm::vec2(std::abs(r_dynamic->vel.x), std::abs(r_dynamic->vel.y)) *
                                  (1 - contact_time);
            return true;
        }

        return false;
    }


};

#endif //MARIO_WORLD_H

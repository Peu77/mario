//
// Created by peu77 on 2/7/22.
//

#include "Brick.h"


Brick::Brick(b2World &world, glm::vec2 spawnPosition) {
    texture = getTexture("res/textures/brick.png");
    position = {spawnPosition.x, spawnPosition.y};

    scale = {100, 100};

    tag = "brick";

    b2BodyDef b_def;

    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t >(this);
    bodyDef.position.Set(tile_width * tile_count / 2 / PIXEL_TO_M, 100 / PIXEL_TO_M);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(tile_width * tile_count / 2 / PIXEL_TO_M, tile_width / 2 / PIXEL_TO_M);

    body->CreateFixture(&groundShape, 0.0f);
}

Brick::~Brick() {
}

void Brick::update(float deleteTime) {
    position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};

}

void Brick::render() {
    for (float i = 0; i <= tile_count; i++)
        Renderer::drawQuad({i * tile_width, tile_width}, {tile_width, tile_width}, texture);
}

void Brick::onCollision(GameObject *object) {

}

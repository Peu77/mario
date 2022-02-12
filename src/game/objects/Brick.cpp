//
// Created by peu77 on 2/7/22.
//

#include "Brick.h"


Brick::Brick(b2World &world, glm::vec2 spawnPosition, float tiles) : tile_count(tiles) {
    texture = getTexture("res/textures/brick.png");
    scale = {100, 100};
    body = new Body();
    body->pos = spawnPosition;
    body->size = scale;
    /*
    position = spawnPosition;



    tag = "brick";

    b2BodyDef b_def;

    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t >(this);
    bodyDef.position.Set((position.x  + tile_count * scale.x ) / PIXEL_TO_M, position.y / PIXEL_TO_M);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox((scale.x * tile_count) / 2.f / PIXEL_TO_M, scale.y / 2.f / PIXEL_TO_M);

    body->CreateFixture(&groundShape, 0.0f);
     */
}

Brick::~Brick() {
}

void Brick::update(float deleteTime) {
    //position = {body->GetPosition().x * PIXEL_TO_M, body->GetPosition().y * PIXEL_TO_M};
}

void Brick::render() {
    Renderer::drawQuad(body->pos, scale, texture);
    /*
    for (float i = 0; i <= tile_count; i++)
        Renderer::drawQuad({(position.x + i * scale.x), position.y}, scale, texture);
        */
}

void Brick::onCollision() {

}

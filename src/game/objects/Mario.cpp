//
// Created by peu77 on 2/7/22.
//

#include <memory>
#include "Mario.h"
#include "irrKlang/include/irrKlang.h"

using namespace irrklang;

//static std::string name = "sysdefault:CARD=Headset";
//static ISoundEngine *SoundEngine = createIrrKlangDevice(irrklang::ESOD_ALSA, ESEO_DEFAULT_OPTIONS, name.c_str());

Mario::Mario(glm::vec2 spawnPosition) {
   //SoundEngine->setSoundVolume(0.02);

    windowId = Renderer::getRenderData()->window;
    textureIdle = getTexture("res/textures/mario.png");
    texture = textureIdle;
    textureJump = getTexture("res/textures/mario-jump.png");
    std::vector<Texture *> textures;
    textures.push_back(getTexture("res/textures/mario-run0.png"));
    textures.push_back(getTexture("res/textures/mario-run1.png"));
    textures.push_back(getTexture("res/textures/mario-run2.png"));
    animation = new Animation(textures);
    lastPosition = spawnPosition;

    body = new Body();
    body->tag = "mario";
    scale = {100, 100};
    body->data = this;
    body->pos = spawnPosition;
    body->size = scale;
    body->dynamic = true;
    body->vel = {0, -70};
}

Mario::~Mario() {
    delete animation;
}

void Mario::update(float deleteTime) {
    body->vel.y -= GRAVITY;
    movement(deleteTime);

    bool bottom = body->contact[0] != nullptr;
    bool right = body->contact[1] != nullptr;
    bool top = body->contact[2] != nullptr;
    bool left = body->contact[3] != nullptr;

    if (body->pos.y < 10) {
        respawn();
    }


    jumping = !bottom;

    if (bottom && !top) {
        if (body->contact[0]->tag == "enemy") {
            body->vel.y = jumpForce / 2;
            auto gameObject = (GameObject *) body->contact[0]->data;
            gameObject->shouldDelete = true;
        }
    }

    bool both = ((glfwGetKey(windowId, GLFW_KEY_A) && glfwGetKey(windowId, GLFW_KEY_D) ) || (left || right));

    if (both && !jumping) {
        texture = textureIdle;
    } else if ((glfwGetKey(windowId, GLFW_KEY_A) || glfwGetKey(windowId, GLFW_KEY_D)) && !jumping) {
        texture = animation->getNext(deleteTime);
    } else if (jumping)
        texture = textureJump;
    else {
        texture = textureIdle;
    }

    if (!both) {
        if (glfwGetKey(windowId, GLFW_KEY_A) && faceRight)
            flip();
        else if (glfwGetKey(windowId, GLFW_KEY_D) && !faceRight)
            flip();
    }

}

void Mario::render() {
    Renderer::drawQuad(body->pos, scale, texture);
    for (int i = 0; i < 4; i++) {

        /*
        if (body->contact[i]) {
            Renderer::drawQuad(body->contact[i]->pos, body->contact[i]->size);
        }
         */

        body->contact[i] = nullptr;
    }
}


void Mario::onCollision() {
    auto bottom = body->contact[0];
    if (bottom != nullptr && bottom->tag == "checkpoint") {
        auto checkpoint = (Checkpoint *) bottom->data;
        checkpoint->active();
        lastPosition = {bottom->pos.x, bottom->pos.y + bottom->size.y};
    }

    for ( auto &item : body->contact)
        if(item != nullptr && item->tag == "bitcoin")
        {
            auto gameObject = (GameObject*) item->data;
            gameObject->shouldDelete = true;
        }

}

float Mario::getVelocityX(float &velocity, float x, float delta) {
    if (body->contact[0] != nullptr && body->contact[0]->tag == "platform") {
        auto offset = (bool *) body->contact[0]->data;

        if (*offset)
            return (90 + body->vel.x) * delta + x;
        else
            return (-90 + body->vel.x) * delta + x;

    }
    return GameObject::getVelocityX(velocity, x, delta);
}

void Mario::movement(float deltaTime) {
    if (glfwGetKey(windowId, GLFW_KEY_A) && glfwGetKey(windowId, GLFW_KEY_D)) {

    } else {
        if (glfwGetKey(windowId, GLFW_KEY_A) == GLFW_PRESS)
            body->vel.x = -speed;
        else if (glfwGetKey(windowId, GLFW_KEY_D) == GLFW_PRESS)

            body->vel.x = speed;
    }


    if (glfwGetKey(windowId, GLFW_KEY_SPACE) == GLFW_PRESS)
        jump();


}


void Mario::respawn() {
    body->pos = lastPosition;
    body->vel.x = 0;
    body->vel.y = 0;
    jumping = false;
}


void Mario::jump() {
    if (body->contact[0] != nullptr) {
       //auto sound = SoundEngine->play2D("res/sound/mario-jump-sound.wav", false, true);
       //sound->setPlayPosition(200);
       // sound->setIsPaused(false);

        jumping = true;
        body->vel.y = jumpForce;
    }
}

void Mario::flip() {
    faceRight = !faceRight;
    scale.x *= -1;
}



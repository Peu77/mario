//
// Created by peu77 on 2/12/22.
//

#include "ScreenEditor.h"

ScreenEditor::ScreenEditor(int &in_width, int &in_height) :
        width(in_width), height(in_height) {
    world = new World(in_width, in_height);
    world->load();


    std::vector<ButtonData *> tags;
    tags.push_back(new ButtonData{this, "mario"});
    tags.push_back(new ButtonData{this, "brick"});
    tags.push_back(new ButtonData{this, "enemy"});
    tags.push_back(new ButtonData{this, "platform"});
    tags.push_back(new ButtonData{this, "checkpoint"});
    tags.push_back(new ButtonData{this, "bitcoin"});
    tags.push_back(new ButtonData{this, "ground"});
    tags.push_back(new ButtonData{this, "backgroundObject"});
    tags.push_back(new ButtonData{this, "#cloud", "res/textures/cloud.png", 256*2, 256*2});
    tags.push_back(new ButtonData{this, "#bush", "res/textures/bush.png", 265*2, 300});

    {
        auto button = new Button();
        button->x = tags.size() * 200 + 30;
        button->width = 100;
        button->height = 50;

        button->buttonFont = Renderer::getRenderData()->font2;
        button->text = "save";
        button->runnable = [](void *screen) {
            auto editor = (ScreenEditor *) screen;

            editor->world->save();
        };
        buttons.push_back(button);
    }

    int offset = 0;

    //generate gameObjects
    for (int i = 0; i < tags.size(); ++i) {
        auto tag = tags[i];
        auto button = new Button();
        button->x = offset;
        button->width = Renderer::getRenderData()->font2->getWidth(tag->tag);
        offset += button->width + 40;
        button->height = 50;

        button->buttonFont = Renderer::getRenderData()->font2;
        button->text = tag->tag;
        button->data = tag;

        button->runnable = [](void *data) {
            auto buttonData = (ButtonData *) data;
            if (!buttonData->tag.starts_with("#"))
                buttonData->screenEditor->currrentTag = buttonData->tag;
            else {
                buttonData->screenEditor->currrentTexture = buttonData->texturePath;
                buttonData->screenEditor->currentTextureWidth = buttonData->textureWidth;
                buttonData->screenEditor->currentTextureHeight = buttonData->textureHeight;
            }
        };

        buttons.push_back(button);
    }

}

ScreenEditor::~ScreenEditor() {
    delete world;
}


void ScreenEditor::draw(int &mouseX, int &mouseY) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    world->renderObjects();
    auto position = getPosition(mouseX, mouseY);
    if (!hoverOverAnyButton(mouseX, mouseY))
        Renderer::drawQuad(position, {100, 100}, {0.4, 0.0, 0.0, 0.4});

    renderButtons(mouseX, mouseY);
}

void ScreenEditor::onClick(int &mouseX, int &mouseY, int &button) {
    if (button == 2) {
        offset = {mouseX, mouseY};
        moving = true;
    }
}

void ScreenEditor::onRelease(int &mouseX, int &mouseY, int &button) {
    bool b = checkButtons(mouseX, mouseY);

    if (button == 2) {
        last.x = std::max(offset.x - mouseX + last.x, 0.0f);
        last.y = std::max(offset.y - mouseY + last.y, 0.0f);

        moving = false;
    } else if (!moving && !b) {
        auto position = getPosition(mouseX, mouseY);
        auto objectOnCords = getGameObject(position.x, position.y);


        int x = (int) position.x;
        int y = (int) position.y;
        auto objectToSpawn = world->genObject(currrentTag, x, y, currrentTexture, currentTextureWidth,
                                              currentTextureHeight);

        if (button == 0 &&
            (objectOnCords == nullptr || (objectOnCords != nullptr && objectOnCords->type != objectToSpawn->type))) {


            if (objectToSpawn != nullptr)
                world->registerBody(objectToSpawn);
        }
        if (button == 1 && objectOnCords != nullptr) {
            world->removeObject(*objectOnCords);
        }

    }
}

void ScreenEditor::update(int &mouseX, int &mouseY, float deltaTime) {
    world->camera->updateProj(width, height);
    if (moving) {
        world->camera->position.x = std::max(offset.x - mouseX + last.x, 0.0f);
        world->camera->position.y = std::max(offset.y - mouseY + last.y, 0.0f);

        world->camera->updateView();
    }


    for (auto &item: buttons)
        item->y = height - item->height / 25;
}

glm::vec2 ScreenEditor::getPosition(int &mouseX, int &mouseY) const {
    double dX = (mouseX + last.x) / 100.0;
    double dY = (mouseY + last.y) / 100.0;
    double x = ((int) dX) * 100;
    double y = ((int) dY) * 100;
    return {x + 50, y + 50};
}

GameObject *ScreenEditor::getGameObject(float &mouseX, float &mouseY) {
    for (const auto &item: world->bodies)
        if (item->body->pos.x == mouseX && item->body->pos.y == mouseY)
            return item;

    return nullptr;
}

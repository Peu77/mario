//
// Created by peu77 on 2/12/22.
//

#include "ScreenEditor.h"

ScreenEditor::ScreenEditor(int &in_width, int &in_height) :
        width(in_width), height(in_height) {
    world = new World(in_width, in_height);
    world->load();

    std::vector<std::string> tags;
    tags.push_back("mario");
    tags.push_back("brick");
    tags.push_back("enemy");
    tags.push_back("platform");
    tags.push_back("checkpoint");
    tags.push_back("bitcoin");

    {
        auto button = new Button();
        button->x = tags.size() * 200 + 30;
        button->y = 50;
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

    for (int i = 0; i < tags.size(); ++i) {
        auto tag = tags[i];
        auto button = new Button();
        button->x = offset;
        button->y = 50;
        button->width = Renderer::getRenderData()->font2->getWidth(tag);
        offset += button->width + 40;
        button->height = 50;

        button->buttonFont = Renderer::getRenderData()->font2;
        button->text = tag;
        button->data = new ButtonData{this, tag};

        button->runnable = [](void *data) {
            auto buttonData = (ButtonData *) data;
            buttonData->screenEditor->currrentTag = buttonData->tag;
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

        if (button == 0 && objectOnCords == nullptr) {
            int x = (int) position.x;
            int y = (int) position.y;
            auto object = world->genObject(currrentTag, x, y);
            if (object != nullptr)
                world->registerBody(object);
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

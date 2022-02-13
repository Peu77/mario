//
// Created by peu77 on 2/12/22.
//

#include "ScreenEditor.h"

ScreenEditor::ScreenEditor(int &in_width, int &in_height) :
        width(in_width), height(in_height) {
    world = new World(in_width, in_height);
    world->load();

    Button button;
    button.x = 200;
    button.y = 200;
    button.width = 200;
    button.height = 100;

    button.buttonFont = Renderer::getRenderData()->font;
    button.text = "save";
    button.runnable = [](void *screen) {
        auto editor = (ScreenEditor *) screen;

        editor->world->save();
    };

    buttons.push_back(button);
}

ScreenEditor::~ScreenEditor() {
    delete world;
}


void ScreenEditor::draw(int &mouseX, int &mouseY) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    world->renderObjects();
    auto position = getPosition(mouseX, mouseY);
    Renderer::drawQuad(position, {100, 100}, {0.4, 0.0, 0.0, 1.0});

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

        auto brick = new Brick(position);
        world->registerBody(brick);
    }
}

void ScreenEditor::update(int &mouseX, int &mouseY, float deltaTime) {
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

GameObject *ScreenEditor::getGameObject(int &mouseX, int &mouseY) {
    

    return nullptr;
}

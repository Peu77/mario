//
// Created by peu77 on 2/12/22.
//

#include "ScreenEditor.h"

ScreenEditor::ScreenEditor(Font *in_font, int &in_width, int &in_height) :
        width(in_width), height(in_height) {
    world = new World();
    camera = new Camera(in_width, in_height);
}

ScreenEditor::~ScreenEditor() {
    delete world;
    delete camera;
}

void ScreenEditor::draw(int &mouseX, int &mouseY) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    world->renderObjects(camera);
}

void ScreenEditor::onClick(int &mouseX, int &mouseY) {

}

void ScreenEditor::onRelease(int &mouseX, int &mouseY) {
    double dX = mouseX / 100.0;
    double dY = mouseY / 100.0;
    double x = ((int) dX) * 100;
    double y = ((int) dY) * 100;


    auto brick = new Brick({x + 50, y + 50});
    world->registerBody(brick);
}

void ScreenEditor::update(float deltaTime) {

}



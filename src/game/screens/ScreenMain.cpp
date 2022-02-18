//
// Created by peu77 on 2/12/22.
//

#include "ScreenMain.h"

Button *gameButton;
Button *editorButton;

ScreenMain::ScreenMain(void (*runnable)(Screen *), int &in_width, int &in_height) :
        Runnable(runnable),
        width(in_width),
        height(in_height) {

    background = getTexture("res/textures/background.jpg");

    {
        gameButton = new Button();
        gameButton->width = 200;
        gameButton->height = 100;
        gameButton->text = "game";

        gameButton->runnable = [](void *data) {
            auto main = (ScreenMain *) data;
            main->Runnable(nullptr);
        };

        gameButton->buttonFont = Renderer::getRenderData()->font;

        buttons.push_back(gameButton);
    }
    {
        editorButton = new Button();
        editorButton->width = 200;
        editorButton->height = 100;
        editorButton->text = "editor";

        editorButton->runnable = [](void *data) {
            auto main = (ScreenMain *) data;
            auto screenEditor = new ScreenEditor(main->width, main->height);
            main->Runnable(screenEditor);
        };

        editorButton->buttonFont = Renderer::getRenderData()->font;

        buttons.push_back(editorButton);
    }
}

void ScreenMain::onButtonClick() {

}

void ScreenMain::draw(int &mouseX, int &mouseY) {
    Renderer::drawQuad({width / 2, height / 2}, {width, height}, background);
    renderButtons(mouseX, mouseY);
}

void ScreenMain::update(int &mouseX, int &mouseY, float deltaTime) {
    gameButton->x = width / 2 - gameButton->width - 10;
    gameButton->y = height / 2 + gameButton->height / 2;

    editorButton->x = width / 2 + 10;
    editorButton->y = height / 2 + editorButton->height / 2;
}

void ScreenMain::onClick(int &mouseX, int &mouseY, int &button) {
}

void ScreenMain::onRelease(int &mouseX, int &mouseY, int &button) {
    checkButtons(mouseX, mouseY);
}

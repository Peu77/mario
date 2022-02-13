//
// Created by peu77 on 2/12/22.
//

#include "ScreenMain.h"

void test() {

}

ScreenMain::ScreenMain(Font *in_font, void (*runnable)(Screen *), int &in_width, int &in_height) : font(in_font),
                                                                                                   Runnable(runnable),
                                                                                                   width(in_width),
                                                                                                   height(in_height) {
    {
        Button button;
        button.x = 500;
        button.y = 500;
        button.width = 200;
        button.height = 100;
        button.text = "game";

        button.runnable = [](void *data) {
            auto main = (ScreenMain *) data;
            main->Runnable(nullptr);
        };

        button.buttonFont = in_font;

        buttons.push_back(button);
    }
    {
        Button button;
        button.x = 500;
        button.y = 650;
        button.width = 200;
        button.height = 100;
        button.text = "editor";

        button.runnable = [](void *data) {
            auto main = (ScreenMain *) data;
            auto screenEditor = new ScreenEditor(main->font, main->width, main->height);
            main->Runnable(screenEditor);
        };

        button.buttonFont = in_font;

        buttons.push_back(button);
    }
}

void ScreenMain::onButtonClick() {

}

void ScreenMain::draw(int &mouseX, int &mouseY) {
    renderButtons(mouseX, mouseY);
}

void ScreenMain::update(int &mouseX, int &mouseY, float deltaTime) {

}

void ScreenMain::onClick(int &mouseX, int &mouseY, int& button) {
}

void ScreenMain::onRelease(int &mouseX, int &mouseY, int& button) {
    checkButtons(mouseX, mouseY);
}

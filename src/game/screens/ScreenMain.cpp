//
// Created by peu77 on 2/12/22.
//

#include "ScreenMain.h"

void test() {

}

ScreenMain::ScreenMain(Font *in_font, void (*runnable)()) : font(in_font), Runnable(runnable) {
    Button button;
    button.x = 500;
    button.y = 500;
    button.width = 200;
    button.height = 100;
    button.text = "game";

    button.runnable = [](void *data) {
        auto main = (ScreenMain *) data;
        main->Runnable();
        screen = nullptr;
    };

    button.buttonFont = in_font;

    buttons.push_back(button);
}

void ScreenMain::onButtonClick() {

}

void ScreenMain::draw(int& mouseX, int& mouseY) {
    renderButtons(mouseX, mouseY);
}

void ScreenMain::update(float deltaTime) {

}

void ScreenMain::onClick(int& mouseX, int& mouseY) {
}

void ScreenMain::onRelease(int& mouseX, int& mouseY) {
    checkButtons(mouseX, mouseY);
}

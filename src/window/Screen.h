//
// Created by peu77 on 2/12/22.
//

#ifndef MARIO_SCREEN_H
#define MARIO_SCREEN_H

#include "vector"
#include "../game/renderer/font.h"
#include "../game/renderer/Renderer.h"
#include "string"

struct Button {
    Font *buttonFont;
    std::string text;
    int x, y, width, height;
    void *data = nullptr;

    void (*runnable)(void *);
};

class Screen {
public:
    std::vector<Button*> buttons;

    virtual void draw(int &mouseX, int &mouseY) = 0;

    virtual void update(int &mouseX, int &mouseY, float deltaTime) = 0;

    virtual void onClick(int &mouseX, int &mouseY, int &button) = 0;

    virtual void onRelease(int &mouseX, int &mouseY, int &button) = 0;

    bool checkButtons(int &mouseX, int &mouseY) {
        for (const Button *item: buttons) {
            if (isHoverButton(*item, mouseX, mouseY)) {
                if (item->data != nullptr)
                    item->runnable(item->data);
                else
                    item->runnable(this);
                return true;
            }
        }
        return false;
    }

    static bool isHoverButton(const Button& button, int &mouseX, int &mouseY) {
        return (mouseX > button.x && mouseX < button.x + button.width &&
                mouseY < button.y && mouseY > button.y - button.height);
    }

    bool hoverOverAnyButton(int &mouseX, int &mouseY) {
        for (const auto* item: buttons)
            if (isHoverButton(*item, mouseX, mouseY))
                return true;

        return false;
    }

    void renderButtons(int &mouseX, int mouseY) {
        Renderer::beginScene(*Renderer::getRenderData()->menuCamera);
        for (const auto* item: buttons) {
            float alpha = 1.0;
            if (isHoverButton(*item, mouseX, mouseY))
                alpha = 0.7;

            Renderer::drawQuad({item->x + item->width / 2, item->y - item->height / 2}, {item->width, item->height},
                               {0.317, 0.941, 0.545, alpha});
            if (item->buttonFont != nullptr) {
                item->buttonFont->RenderText(item->text,
                                            (float) item->x + item->width / 2 - item->buttonFont->getWidth(item->text) / 2,
                                            (float) item->y - item->buttonFont->getHeight(), 1.0f,
                                            {1.0f, 1.0f, 1.0f, alpha});
            }
        }
    }
};


#endif //MARIO_SCREEN_H

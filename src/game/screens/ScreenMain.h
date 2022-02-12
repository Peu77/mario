//
// Created by peu77 on 2/12/22.
//

#ifndef MARIO_SCREENMAIN_H
#define MARIO_SCREENMAIN_H

#include "../../window/Screen.h"
#include "../renderer/font.h"
#include "../Game.h"

class ScreenMain : public Screen {

private:
    Font* font;
    void (*Runnable)();

public:
    void onButtonClick();

    ScreenMain(Font* in_font, void (*runnable)());

    void draw(int& mouseX, int& mouseY) override;

    void onClick(int& mouseX, int& mouseY) override;

    void onRelease(int& mouseX, int& mouseY) override;

    void update(float deltaTime) override;
};


#endif //MARIO_SCREENMAIN_H

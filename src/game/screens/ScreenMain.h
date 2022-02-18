//
// Created by peu77 on 2/12/22.
//

#ifndef MARIO_SCREENMAIN_H
#define MARIO_SCREENMAIN_H

#include "../../window/Screen.h"
#include "../Game.h"
#include "../screens/ScreenEditor.h"
#include "../renderer/Renderer.h"

class ScreenMain : public Screen {

private:
    void (*Runnable)(Screen*);
    int& width, &height;

public:
    void onButtonClick();

    ScreenMain(void (*runnable)(Screen*), int& in_width, int& in_height );

    void draw(int& mouseX, int& mouseY) override;

    void onClick(int& mouseX, int& mouseY, int& button) override;

    void onRelease(int& mouseX, int& mouseY, int& button) override;

    void update(int &mouseX, int &mouseY, float deltaTime) override;

private:
    Texture* background;
};


#endif //MARIO_SCREENMAIN_H

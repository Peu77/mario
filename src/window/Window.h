//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_WINDOW_H
#define MARIO_WINDOW_H

#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"

class Window {
private:
    int Width, Height;

public:
    GLFWwindow* WindowId;

    Window(const char *title, int width, int height);
    ~Window();
};


#endif //MARIO_WINDOW_H

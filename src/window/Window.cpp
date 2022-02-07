//
// Created by peu77 on 2/7/22.
//

#include "Window.h"

Window::Window(const char *title, int width, int height) :
        Width(width), Height(height) {

    WindowId = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwSetWindowSizeLimits(WindowId, width, height, width, height);
    if (!WindowId) {
        glfwTerminate();
    }
    glfwMakeContextCurrent(WindowId);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        printf("Failed to initialize Glad.\n");

    std::cout << "create window" << std::endl;
}

Window::~Window() {
    std::cout << "delete window" << std::endl;
    glfwTerminate();
}

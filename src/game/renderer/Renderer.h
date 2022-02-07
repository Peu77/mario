//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_RENDERER_H
#define MARIO_RENDERER_H

#include "../camera/Camera.h"
#include "../shader/Program.h"
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"

struct RenderData {
    unsigned int vertexArray;
    unsigned int arrayBuffer;
    unsigned int indexBuffer;
    Program* program;
};

static RenderData* renderData;

class Renderer {
public:
    static void init();

    static void shutdown();

    static void beginScene(const Camera &camera);

    static void drawQuad(glm::vec2 position, glm::vec2 scale);
};


#endif //MARIO_RENDERER_H

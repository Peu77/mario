//
// Created by peu77 on 2/7/22.
//

#ifndef MARIO_RENDERER_H
#define MARIO_RENDERER_H

#include "../camera/Camera.h"
#include "../shader/Program.h"
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "../texture/Texture.h"
#include "font.h"

struct RenderData {
    unsigned int vertexArray;
    unsigned int arrayBuffer;
    unsigned int indexBuffer;
    Program *program;
    Program *programTexture;
    Font *font;
    Font *font2;
    Camera *menuCamera;
    GLFWwindow* window;
};

static RenderData *renderData;


class Renderer {
public:
    static void init(int &in_width, int &in_height, GLFWwindow* window);

    static RenderData* getRenderData();

    static void shutdown();

    static void beginScene(const Camera &camera);

    static void drawQuad(glm::vec2 position, glm::vec2 scale);

    static void drawQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color);

    static void drawQuad(glm::vec2 position, glm::vec2 scale, Texture *texture);
};


#endif //MARIO_RENDERER_H

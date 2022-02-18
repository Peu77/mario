//
// Created by peu77 on 2/7/22.
//

#include "Renderer.h"

void Renderer::init(int &in_width, int &in_height, GLFWwindow *window) {
    renderData = new RenderData();
    renderData->window = window;
    renderData->programTexture = Program::loadProgram("texture");
    renderData->program = Program::loadProgram("color");
    auto fontShader = Program::loadProgram("font");

    renderData->menuCamera = new Camera(in_width, in_height);
    renderData->font = new Font(&renderData->menuCamera->proj, fontShader, 58);
    renderData->font2 = new Font(&renderData->menuCamera->proj, fontShader, 30);

    float positions[] = {
            -0.5f, -0.5f, 0.f, 0.f,
            -0.5f, 0.5f, 0.f, 1.f,
            0.5f, 0.5f, 1.f, 1.f,
            0.5f, -0.5f, 1.f, 0.f
    };

    unsigned int indices[] = {
            0, 1, 2, 2, 3, 0
    };

    glGenBuffers(1, &renderData->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, renderData->vertexArray);

    glGenBuffers(1, &renderData->arrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, renderData->arrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void *) (sizeof(float) * 0));

    glGenBuffers(1, &renderData->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderData->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    renderData->programTexture->bind();
    renderData->programTexture->uploadUniform1i("u_Tex", 0);
}

RenderData *Renderer::getRenderData() {
    return renderData;
}

void Renderer::shutdown() {
    glDeleteVertexArrays(1, &renderData->vertexArray);
    glDeleteBuffers(1, &renderData->arrayBuffer);
    glDeleteBuffers(1, &renderData->indexBuffer);

    delete renderData;
}

void Renderer::beginScene(const Camera &camera) {
    renderData->program->bind();
    renderData->program->uploadUniformMat4f("u_view", camera.view);
    renderData->program->uploadUniformMat4f("u_projection", camera.proj);

    renderData->programTexture->bind();
    renderData->programTexture->uploadUniformMat4f("u_view", camera.view);
    renderData->programTexture->uploadUniformMat4f("u_projection", camera.proj);
}

void Renderer::drawQuad(glm::vec2 position, glm::vec2 scale) {
    drawQuad(position, scale, {1.0, 0.0, 0.0, 1.0});
}

void Renderer::drawQuad(glm::vec2 position, glm::vec2 scale, Texture *texture) {
    glm::mat4 model =
            glm::translate(glm::mat4(1), {position.x, position.y, 0});

    model = glm::scale(model, {scale.x, scale.y, 0});

    renderData->programTexture->bind();

    auto lights = renderData->lights;
    auto light_size = lights->size();

    if (light_size == 0) {
        //add light temp light, that the game not crash when the size is 0 :D

        auto *x = new float{-100};

        renderData->lights->push_back(x);
        renderData->lights->push_back(x);
    }

    renderData->programTexture->uploadUniformMat4f("u_model", model);
    renderData->programTexture->uploadUniform1i("light_size", light_size);

    float array[light_size];

    for (int i = 0; i < light_size; ++i) {
        array[i] = *lights->at(i);
    }

    renderData->programTexture->uploadUniform1farray("lights", light_size, array);

    texture->Bind();
    glBindVertexArray(renderData->vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderData->indexBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::drawQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color) {
    glm::mat4 model =
            glm::translate(glm::mat4(1), {position.x, position.y, 0});

    model = glm::scale(model, {scale.x, scale.y, 0});

    renderData->program->bind();
    renderData->program->uploadUniformMat4f("u_model", model);
    renderData->program->uploadUniform4f("color", color.x, color.y, color.z, color.w);

    glBindVertexArray(renderData->vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderData->indexBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

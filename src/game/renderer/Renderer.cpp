//
// Created by peu77 on 2/7/22.
//

#include "Renderer.h"

void Renderer::init() {
    renderData = new RenderData();
    Shader vertex("res/shaders/main.vertex", GL_VERTEX_SHADER);
    Shader fragment("res/shaders/main.fragment", GL_FRAGMENT_SHADER);
    renderData->program = new Program(&vertex, &fragment);

    float positions[] = {
            0.0f , 0.0f , // left bottom
            0.5f, 0.0f , // right bottom
            0.5f , 0.5f , // right top
            0.0f , 0.5f   // left top
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void *) (sizeof(float) * 0));

    glGenBuffers(1, &renderData->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderData->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
}

void Renderer::drawQuad(glm::vec2 position, glm::vec2 scale) {
    glm::mat4 model =
            glm::translate(glm::mat4(1), {position.x, position.y, 0}) * glm::scale(glm::mat4(1), {scale.x, scale.y, 0});


    renderData->program->bind();
    renderData->program->uploadUniformMat4f("u_model", model);

    glBindVertexArray(renderData->vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderData->indexBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

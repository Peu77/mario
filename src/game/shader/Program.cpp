//
// Created by peu77 on 2/4/22.
//

#include "Program.h"

Program::Program(Shader *vertexShader, Shader *fragmentShader)
        : VertexShader(*vertexShader), FragmentShader(*fragmentShader) {
    std::cout << "create program" << std::endl;
    link();
    bind();
}

void Program::link() {
    std::cout << "try to link" << std::endl;
    unsigned int program = glCreateProgram();

    unsigned fragmentId = this->FragmentShader.ShaderId;
    unsigned vertexId = this->VertexShader.ShaderId;

    glAttachShader(program, fragmentId);
    glAttachShader(program, vertexId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(fragmentId);
    glDeleteShader(vertexId);
    this->ProgramId = program;
}

void Program::bind() {
    glUseProgram(ProgramId);
}

void Program::uploadUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    auto location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

int Program::getUniformLocation(const std::string &name) {
    if (UniformLocationCache.contains(name))
        return UniformLocationCache[name];

    int location = glGetUniformLocation(this->ProgramId, name.c_str());

    if (location == -1)
        std::cout << "Warning: uniform: '" << name << "' doesn't exist" << std::endl;
    else {
        UniformLocationCache[name] = location;
    }
    return location;
}

void Program::uploadUniform2f(const std::string &name, float v0, float v1) {
    glUniform2f(getUniformLocation(name), v0, v1);
}

void Program::uploadUniform1i(const std::string &name, int i) {
    glUniform1i(getUniformLocation(name), i);
}

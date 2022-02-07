//
// Created by peu77 on 2/4/22.
//

#include "Shader.h"


Shader::Shader(std::string filepath, unsigned int type) : Filepath(std::move(filepath)), ShaderId(0), Type(type) {
    compileShader();
}

Shader::~Shader() {
    glDeleteProgram(ShaderId);
};

std::string Shader::readShader() {
    std::ifstream stream(Filepath);

    std::string line;
    std::stringstream ss[1];
    while (getline(stream, line)) {
        ss[0] << line << '\n';
    }

    return ss[0].str();
}

void Shader::compileShader() {
    std::string typeString = (Type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
    std::cout << "compile shader" << typeString << std::endl;
    std::string source = this->readShader();

    unsigned int id = glCreateShader(Type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" << typeString << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }

    std::cout << "done" << std::endl;

    ShaderId = id;
}





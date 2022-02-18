//
// Created by peu77 on 2/4/22.
//

#ifndef MARIO_PROGRAM_H
#define MARIO_PROGRAM_H

#include "Shader.h"


class Program {
private:
    Shader VertexShader;
    Shader FragmentShader;
    unsigned int ProgramId{};
    std::unordered_map<std::string, int> UniformLocationCache;
    int getUniformLocation(const std::string &name);


public:
    Program(Shader *vertexShader, Shader *fragmentShader);

    void link();

    void bind();

    void uploadUniformMat4f(const std::string& name, const glm::mat4& matrix);
    void uploadUniform2f(const std::string& name, float v0, float v1);
    void uploadUniform1farray(const std::string& name,int size, float *v);
    void uploadUniform3f(const std::string& name, float v0, float v1, float v2);
    void uploadUniform4f(const std::string& name, float v0, float v1, float v2,float v3);
    void uploadUniform1i(const std::string& name, int i);
    void uploadUniform1f(const std::string& name, float v);


    static Program* loadProgram(const std::string& name);
};


#endif //PONG_PROGRAM_H

//
// Created by peu77 on 2/4/22.
//

#ifndef PONG_SHADER_H
#define PONG_SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <glad/include/glad/glad.h>
#include "../libs/glm/glm.hpp"



class Shader {
public:
    unsigned int ShaderId;
    std::string Filepath;
    unsigned int Type;


    Shader(std::string filepath, unsigned int type);

    ~Shader();

public:
    std::string readShader();

    void compileShader();
};


#endif //PONG_SHADER_H

//
// Created by peu77 on 12/27/21.
//

#ifndef MARIO_TEXTURE_H
#define MARIO_TEXTURE_H

#include "iostream"
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include <unordered_map>

class Texture {
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    static std::unordered_map<std::string, Texture *> textureCache;

public:
    static Texture* getTexture(const std::string& path);

public:
    Texture(const std::string &path);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    void Unbind();

    inline int GetWidth() const { return m_Width; }

    inline int GetHeight() const { return m_Height; }
};


#endif //MARIO_TEXTURE_H

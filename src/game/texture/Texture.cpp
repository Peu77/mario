//
// Created by peu77 on 12/27/21.
//

#include "Texture.h"
#include "../../../libs/std_image/std_image.h"

Texture *Texture::getTexture(const std::string& path) {
    if(textureCache.contains(path)){
        std::cout << "load texture: " << path << " from cache" << std::endl;
        return textureCache[path];
    }

    auto* texture = new Texture(path);
    textureCache[path] = texture;

    return texture;
}

Texture::Texture(const std::string &path)
:m_RendererID(0) ,m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // GL_CLAMP_TO_EDGE  GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// GL_CLAMP_TO_EDGE

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(m_LocalBuffer){
        stbi_image_free(m_LocalBuffer);
    }

}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);
}

void Texture:: Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}


#include "../../texture.h"

#include <glad/glad.h>

#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Kasumi::Texture::Texture(const std::string &path) : _path(std::move(path))
{
    ID = _width = _height = _nr_channels = 0;
    unsigned char *data = stbi_load(path.c_str(), &_width, &_height, &_nr_channels, 0);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}
#include <iostream>
Kasumi::Texture::~Texture()
{
    std::cout << "delete texture: " << _path << std::endl;
}

void Kasumi::Texture::bind(int texture_idx) const
{
    switch (texture_idx)
    {
        case 0:
            glActiveTexture(GL_TEXTURE0);
            break;
        case 1:
            glActiveTexture(GL_TEXTURE1);
            break;
        case 2:
            glActiveTexture(GL_TEXTURE2);
            break;
        case 3:
            glActiveTexture(GL_TEXTURE3);
            break;
        case 4:
            glActiveTexture(GL_TEXTURE4);
            break;
        default: // TOO MUCH TEXTURES
            break;
    }
    glBindTexture(GL_TEXTURE_2D, ID);
}

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifndef __WIN32__
    #include <SDL.h>
#endif

#include "texture.h"

Texture::Texture()
{
    m_width = 0;
    m_height = 0;
}
Texture::~Texture()
{
    glDeleteTextures( 1, &m_id );
}

void Texture::bind(const int channel)
{
    glActiveTexture(GL_TEXTURE0+channel);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::load(const std::string &filename)
{
    int comp;
    #ifdef __WIN32__
        unsigned char *data = stbi_load(filename.c_str(), &m_width, &m_height, &comp, 0);
    #else
        SDL_RWops *file;
        file = SDL_RWFromFile(filename.c_str(), "rb");
        if(!file)
        {
            SDL_Log( "Can't read %s\n", filename.c_str());
            return;
        }

        size_t length = SDL_RWseek(file, 0, SEEK_END);
        unsigned char* dataImg = new unsigned char[length];
        memset(dataImg, 0x00, length);

        SDL_RWseek(file, 0, SEEK_SET);
        int n_blocks = SDL_RWread(file, dataImg, 1, length);
        SDL_RWclose(file);
        unsigned char *data = stbi_load_from_memory(dataImg, length, &m_width, &m_height, &comp, 0);
    #endif

    if(!data)
    {
        //std::cout << "Failed to load texture" << filename << std::endl;
        return;
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if(comp == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width,m_height, 0, GL_RGB,GL_UNSIGNED_BYTE, data);
    else if(comp == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

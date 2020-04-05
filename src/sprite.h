#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>

#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();

    //Accessors
    void setShader( const std::string &vertex, const std::string &fragment);
    void setTexture( const std::string &filename);
    void setPosition( const glm::vec2 &p );
    void setSize( const glm::vec2 &s);

    glm::vec2& getPosition();
    glm::vec2& getSize();
    void draw();


private:
    Texture m_tex;
    Shader m_shader;
    glm::vec2 m_pos;
    glm::vec2 m_size;

};

#endif // TEXT_H

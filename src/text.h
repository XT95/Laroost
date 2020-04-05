#ifndef TEXT_H
#define TEXT_H

#include <iostream>

#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"

class Text
{
public:
    Text();
    ~Text();

    //Accessors
    void setShader( const std::string &vertex, const std::string &fragment);
    void setFont(Texture *tex );
    void setText( const std::string &txt);
    void setPosition( const glm::vec2 &p );
    void setSize( const float s);

    Texture* getFont();
    std::string& getText();
    glm::vec2& getPosition();
    float getSize();
    void draw();


private:
    Texture *m_tex;
    std::string m_txt;
    Shader *m_shader;
    glm::vec2 m_pos;
    float m_size;

};

#endif // TEXT_H

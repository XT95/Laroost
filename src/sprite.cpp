#include "fast2dquad.h"
#include "sprite.h"
#include "core.h"


Sprite::Sprite() :
    m_size(1./32.f)
{

}

Sprite::~Sprite()
{

}

void Sprite::setShader( const std::string &vertex, const std::string &fragment)
{
    m_shader.load(vertex.c_str(), NULL, fragment.c_str());
}

void Sprite::setTexture( const std::string &filename )
{
    m_tex.load(filename);
}

void Sprite::setPosition( const glm::vec2 &p )
{
    m_pos = p;
}
void Sprite::setSize(const glm::vec2 &s)
{
    m_size = s;
}


glm::vec2& Sprite::getPosition()
{
    return m_pos;
}
glm::vec2& Sprite::getSize()
{
    return m_size;
}


void Sprite::draw()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    m_tex.bind(0);

    m_shader.enable();
    m_shader.send("tex",0);
    m_shader.send("size", m_size);
    m_shader.send("pos", m_pos);

    Fast2DQuad::instance().render();

    m_shader.disable();


    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

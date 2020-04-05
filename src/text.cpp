#include "fast2dquad.h"
#include "text.h"
#include "core.h"


Text::Text() :
    m_size(1./32.f)
{
    m_shader = &Core::instance().shaderText;
    m_tex = &Core::instance().font;
}

Text::~Text()
{

}

void Text::setShader( const std::string &vertex, const std::string &fragment)
{
    m_shader = new Shader();
    m_shader->load(vertex.c_str(), NULL, fragment.c_str());
}

void Text::setFont( Texture *tex )
{
    m_tex = tex;
}

void Text::setText( const std::string &txt)
{
    m_txt = txt;
}

void Text::setPosition( const glm::vec2 &p )
{
    m_pos = p;
}
void Text::setSize(const float s)
{
    m_size = s;
}


Texture* Text::getFont()
{
    return m_tex;
}
std::string& Text::getText()
{
    return m_txt;
}
glm::vec2& Text::getPosition()
{
    return m_pos;
}
float Text::getSize()
{
    return m_size;
}


void Text::draw()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    m_tex->bind(0);

    m_shader->enable();
    m_shader->send("tex",0);
    m_shader->send("size", m_size);

    for(int i=0; i<m_txt.size(); i++)
    {
        char c = m_txt[i];
        if(c=='\0')
            break;
        glm::vec2 p(m_pos + glm::vec2(m_size*i*2.,0.));
        glm::vec2 offset( float((c-32)%16)/16.f,
                          float((c-32)/16)/16.f);

        m_shader->send("pos", p);
        m_shader->send("offset", offset);
        m_shader->send("time", Core::instance().time);
        Fast2DQuad::instance().render();

    }

    m_shader->disable();


    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

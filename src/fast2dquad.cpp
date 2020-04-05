#include "fast2dquad.h"


Fast2DQuad Fast2DQuad::m_instance=Fast2DQuad();

Fast2DQuad::Fast2DQuad()
{

}

Fast2DQuad::~Fast2DQuad()
{

}

Fast2DQuad& Fast2DQuad::instance()
{
    return m_instance;
}

void Fast2DQuad::init()
{
    float vertex[4][3];
    vertex[0][0] =-1.0f; vertex[1][0] = 1.0f; vertex[2][0] =-1.0f; vertex[3][0] = 1.0f;
    vertex[0][1] =-1.0f; vertex[1][1] =-1.0f; vertex[2][1] = 1.0f; vertex[3][1] = 1.0f;
    for(int i=0; i<4; i++)
        vertex[i][2] = 0.f;

    //make the vertex buffer object
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //make the vertex array object
    #ifdef __WIN32__
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);
    #endif


    m_shader.load("Data/Shaders/shader.vs",NULL,"Data/Shaders/shader.fs");
    m_shader.enable();
     m_shader.send("input", 0);
    m_shader.disable();

}
void Fast2DQuad::render()
{
    #ifdef __WIN32__
        glBindVertexArray(m_vao);
    #else
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    #endif
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#ifdef __WIN32__
    glBindVertexArray(0);
#endif
}
void Fast2DQuad::free()
{
    glDeleteBuffers(1,&m_vbo);

    #ifdef __WIN32__
        glDeleteVertexArrays(1,&m_vao);
    #endif
}


void Fast2DQuad::enableBasicShading()
{
    m_shader.enable();
}


void Fast2DQuad::disableBasicShading()
{
    m_shader.disable();
}

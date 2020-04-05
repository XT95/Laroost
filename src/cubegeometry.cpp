#include <iostream>
#include "cubegeometry.h"


static GLfloat m_data[] =
{
    // pos x3, normals x3, texcoord x2
    1.0f, -1.0f, -1.0f,        1.0f, 0.0f, 0.0f,        0.f, 0.f,
    1.0f, 1.0f, -1.0f,         1.0f, 0.0f, 0.0f,        1.f, 0.f,
    1.0f, -1.0f, 1.0f,         1.0f, 0.0f, 0.0f,        0.f, 1.f,
    1.0f, -1.0f, 1.0f,         1.0f, 0.0f, 0.0f,        0.f, 1.f,
    1.0f, 1.0f, -1.0f,         1.0f, 0.0f, 0.0f,        1.f, 0.f,
    1.0f, 1.0f, 1.0f,          1.0f, 0.0f, 0.0f,        1.f, 1.f,

    1.0f, 1.0f, -1.0f,         0.0f, 1.0f, 0.0f,        1.f, 0.f,
    -1.0f, 1.0f, -1.0f,        0.0f, 1.0f, 0.0f,        0.f, 0.f,
    1.0f, 1.0f, 1.0f,          0.0f, 1.0f, 0.0f,        1.f, 1.f,
    1.0f, 1.0f, 1.0f,          0.0f, 1.0f, 0.0f,        1.f, 1.f,
    -1.0f, 1.0f, -1.0f,        0.0f, 1.0f, 0.0f,        0.f, 0.f,
    -1.0f, 1.0f, 1.0f,         0.0f, 1.0f, 0.0f,        0.f, 1.f,

    -1.0f, 1.0f, -1.0f,        -1.0f, 0.0f, 0.0f,        1.f, 0.f,
    -1.0f, -1.0f, -1.0f,       -1.0f, 0.0f, 0.0f,        0.f, 0.f,
    -1.0f, 1.0f, 1.0f,         -1.0f, 0.0f, 0.0f,        1.f, 1.f,
    -1.0f, 1.0f, 1.0f,         -1.0f, 0.0f, 0.0f,        1.f, 1.f,
    -1.0f, -1.0f, -1.0f,       -1.0f, 0.0f, 0.0f,        0.f, 0.f,
    -1.0f, -1.0f, 1.0f,        -1.0f, 0.0f, 0.0f,        0.f, 1.f,

    -1.0f, -1.0f, -1.0f,       0.0f, -1.0f, 0.0f,        0.f, 0.f,
    1.0f, -1.0f, -1.0f,        0.0f, -1.0f, 0.0f,        1.f, 0.f,
    -1.0f, -1.0f, 1.0f,        0.0f, -1.0f, 0.0f,        0.f, 1.f,
    -1.0f, -1.0f, 1.0f,        0.0f, -1.0f, 0.0f,        0.f, 1.f,
    1.0f, -1.0f, -1.0f,        0.0f, -1.0f, 0.0f,        1.f, 0.f,
    1.0f, -1.0f, 1.0f,         0.0f, -1.0f, 0.0f,        1.f, 1.f,

    1.0f, 1.0f, 1.0f,          0.0f, 0.0f, 1.0f,        1.f, 0.f,
    -1.0f, 1.0f, 1.0f,         0.0f, 0.0f, 1.0f,        0.f, 0.f,
    1.0f, -1.0f, 1.0f,         0.0f, 0.0f, 1.0f,        1.f, 1.f,
    1.0f, -1.0f, 1.0f,         0.0f, 0.0f, 1.0f,        1.f, 1.f,
    -1.0f, 1.0f, 1.0f,         0.0f, 0.0f, 1.0f,        0.f, 0.f,
    -1.0f, -1.0f, 1.0f,        0.0f, 0.0f, 1.0f,        0.f, 1.f,

    1.0f, -1.0f, -1.0f,        0.0f, 0.0f, -1.0f,        1.f, 0.f,
    -1.0f, -1.0f, -1.0f,       0.0f, 0.0f, -1.0f,        0.f, 0.f,
    1.0f, 1.0f, -1.0f,         0.0f, 0.0f, -1.0f,        1.f, 1.f,
    1.0f, 1.0f, -1.0f,         0.0f, 0.0f, -1.0f,        1.f, 1.f,
    -1.0f, -1.0f, -1.0f,       0.0f, 0.0f, -1.0f,        0.f, 0.f,
    -1.0f, 1.0f, -1.0f,        0.0f, 0.0f, -1.0f,        0.f, 1.f
};


CubeGeometry::CubeGeometry()
{
    #ifdef __WIN32__
        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);
    #endif
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_data), m_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));

#ifdef __WIN32__
    glBindVertexArray(0);
#endif
}

CubeGeometry::~CubeGeometry()
{
    glDeleteBuffers(1, &m_vertexBuffer);
#ifdef __WIN32__
    glDeleteVertexArrays(1, &m_vertexArray);
#endif
}

void CubeGeometry::draw()
{
#ifdef __WIN32__
    glBindVertexArray(m_vertexArray);
#else
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
#endif
    glDrawArrays(GL_TRIANGLES, 0, 6*6);

}

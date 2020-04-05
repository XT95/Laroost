#include "planegeometry.h"
#define SIZE 1.f

static GLfloat m_data[] =
{
    // pos x3, normals x3, texcoord x2
     SIZE, 0.0f, -SIZE,        0.0f, 1.0f, 0.0f,        1.f, 0.f,
    -SIZE, 0.0f, -SIZE,        0.0f, 1.0f, 0.0f,        0.f, 0.f,
     SIZE, 0.0f,  SIZE,        0.0f, 1.0f, 0.0f,        1.f, 1.f,
     SIZE, 0.0f,  SIZE,        0.0f, 1.0f, 0.0f,        1.f, 1.f,
    -SIZE, 0.0f, -SIZE,        0.0f, 1.0f, 0.0f,        0.f, 0.f,
    -SIZE, 0.0f,  SIZE,        0.0f, 1.0f, 0.0f,        0.f, 1.f,
};

PlaneGeometry::PlaneGeometry( int size )
{
    for(int i=0; i<6; i++)
    {
        m_data[i*8] *= size;
        m_data[i*8+2] *= size;
    }
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

PlaneGeometry::~PlaneGeometry()
{
    glDeleteBuffers(1, &m_vertexBuffer);
#ifdef __WIN32__
    glDeleteVertexArrays(1, &m_vertexArray);
#endif
}

void PlaneGeometry::draw()
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
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

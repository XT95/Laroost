#ifndef CUBEGEOMETRY_H
#define CUBEGEOMETRY_H

#include "geometry.h"
#ifdef __WIN32__
	#include <GL/glew.h>
#else
	#include <GLES2/gl2.h>
#endif

class CubeGeometry : public Geometry
{
public:
    CubeGeometry();
    ~CubeGeometry();

    void draw();
protected:
    GLuint m_vertexArray;
    GLuint m_vertexBuffer;
};

#endif // CUBEGEOMETRY_H

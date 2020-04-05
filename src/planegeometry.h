#ifndef PLANEGEOMETRY_H
#define PLANEGEOMETRY_H

#include "geometry.h"
#ifdef __WIN32__
	#include <GL/glew.h>
#else
	#include <GLES2/gl2.h>
#endif


class PlaneGeometry : public Geometry
{
public:
    PlaneGeometry(int size = 1);
    ~PlaneGeometry();
    void draw();
protected:
    GLuint m_vertexArray;
    GLuint m_vertexBuffer;
};

#endif // PLANEGEOMETRY_H

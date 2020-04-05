#ifndef SPACESHIPGEOMETRY_H
#define SPACESHIPGEOMETRY_H


#include "geometry.h"
#ifdef __WIN32__
	#include <GL/glew.h>
#else
	#include <GLES2/gl2.h>
#endif


class SpaceshipGeometry : public Geometry
{
public:
    SpaceshipGeometry();
    ~SpaceshipGeometry();
    void draw();
protected:
    GLuint m_vertexArray;
    GLuint m_vertexBuffer;
};

#endif // SPACESHIPGEOMETRY_H

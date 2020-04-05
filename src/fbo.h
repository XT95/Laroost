#ifndef DEF_CORE_FBO_H
#define DEF_CORE_FBO_H
#ifdef __WIN32__
       #include <GL/glew.h>
#else
       #include <GLES2/gl2.h>
#endif

#include "texture.h"

//-----------------------------------------------------------------------------
// Class Frame Buffer Object
//-----------------------------------------------------------------------------
class FBO : public Texture
{
public:
       FBO();
       ~FBO();

       void enable(void);
       void disable(void);


       void setSize( int width, int height );
       void setFormat(GLint format);

       GLuint getFrameBuffer(void);
       GLuint getColor(void);
       GLenum getFormat(){return m_format;}

       void bind(const int channel);
private:
       void updateTexture();

       GLuint m_FrameBuffer;
       GLuint m_DepthRenderBuffer;
       GLuint m_ColorTextureID;
       GLint  m_format;

       int m_viewport[4];
};


#endif

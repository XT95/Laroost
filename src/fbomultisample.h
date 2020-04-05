#ifndef FBOMULTISAMPLE_H
#define FBOMULTISAMPLE_H

#ifdef __WIN32__
    #include <GL/glew.h>
#else
    #include <GLES2/gl2.h>
#endif
#include "fbo.h"
#include "texture.h"

class FBOMultiSample : public Texture
{
public:
    FBOMultiSample(int numSamples = -1);
    ~FBOMultiSample();

    void enable(void);
    void disable(void);


    void setSize( int width, int height );
    void setFormat(GLint format);

    GLuint getColor(void);
    GLenum getFormat(){return m_format;}

    void bind(const int channel);
    void blit(FBO *fbo);
private:
    void updateTexture();

    GLuint m_FrameBuffer;
    GLuint m_ColorRenderBuffer;
    GLuint m_DepthRenderBuffer;
    GLuint m_ColorTextureID;
    GLint  m_format;
    GLint  m_numSamples;

    int m_viewport[4];
};

#endif // FBOMUTLISAMPLE_H

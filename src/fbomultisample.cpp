#include "fbomultisample.h"

#include <iostream>


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
FBOMultiSample::FBOMultiSample( int numSamples ) : Texture()
{
    m_width = 1280;
    m_height = 720;
    m_format = GL_RGBA;


    glGetIntegerv(GL_MAX_SAMPLES, &numSamples);
    //std::cout << numSamples << std::endl;
    m_numSamples = numSamples;


    glGenTextures(1, &m_ColorTextureID);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorTextureID);
    glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, m_numSamples, GL_RGBA8, m_width, m_height, GL_TRUE );
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    glGenFramebuffers(1, &m_FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_ColorTextureID, 0);

    glGenRenderbuffers(1, &m_ColorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, GL_RGBA, m_width, m_height);

    glGenRenderbuffers(1, &m_DepthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, GL_DEPTH_COMPONENT24, m_width, m_height);


    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_ColorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBuffer);


/*    GLenum  g_DrawBufferStatusCheck_ENUM = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

    switch (g_DrawBufferStatusCheck_ENUM)
    {
     case GL_FRAMEBUFFER_COMPLETE:
        //std::cout << "ok" << std::endl;
     break;
     case GL_FRAMEBUFFER_UNSUPPORTED:
     //Choose different formats
     std::cout << "Framebuffer object format is unsupported by the video hardware. (GL_FRAMEBUFFER_UNSUPPORTED)(FBO - 820)" << std::endl;
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
     std::cout << "Incomplete attachment. (GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)(FBO - 820)" << std::endl;
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
     std::cout << "Incomplete missing attachment. (GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)(FBO - 820)" << std::endl;
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
     std::cout << "Incomplete dimensions. (GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS)(FBO - 820)" << std::endl;
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
     std::cout << "Incomplete formats. (GL_FRAMEBUFFER_INCOMPLETE_FORMATS)(FBO - 820)" << std::endl;
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
     std::cout << "Incomplete draw buffer. (GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)(FBO - 820)" << std::endl;
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
     std::cout << "Incomplete read buffer. (GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)(FBO - 820)" << std::endl;
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
     std::cout << "Incomplete multisample buffer. (GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)(FBO - 820)" << std::endl;
     break;
     default:
     //Programming error; will fail on all hardware
     std::cout << "Some video driver error or programming error occured. Framebuffer object status is invalid. (FBO - 823)" << std::endl;
     break;
     }*/


    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
FBOMultiSample::~FBOMultiSample()
{
    glDeleteTextures(1, &m_ColorTextureID);
    glDeleteRenderbuffers(1, &m_ColorRenderBuffer);
    glDeleteRenderbuffers(1, &m_DepthRenderBuffer);
    glDeleteFramebuffers(1, &m_FrameBuffer);
}


//-----------------------------------------------------------------------------
// Enable
//-----------------------------------------------------------------------------
void FBOMultiSample::enable(void)
{
    glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0,0,m_width,m_height);
    glEnable(GL_MULTISAMPLE);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}

//-----------------------------------------------------------------------------
// Disable
//-----------------------------------------------------------------------------
void FBOMultiSample::disable(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_MULTISAMPLE);
    glPopAttrib();
}



//-----------------------------------------------------------------------------
// Set
//-----------------------------------------------------------------------------
void FBOMultiSample::setSize( int width, int height )
{
    m_width = width;
    m_height = height;


    updateTexture();
}
void FBOMultiSample::setFormat(GLint format)
{
    m_format = format;
    updateTexture();
}


//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
GLuint FBOMultiSample::getColor(void)
{
    return m_ColorTextureID;
}

//-----------------------------------------------------------------------------
// updateTexture
//-----------------------------------------------------------------------------
void FBOMultiSample::updateTexture()
{
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorTextureID);
    glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, m_numSamples, GL_RGBA8, m_width, m_height, GL_TRUE );

    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, GL_RGBA, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_ColorRenderBuffer);

    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, GL_DEPTH_COMPONENT24, m_width, m_height);


    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

//-----------------------------------------------------------------------------
// bind
//-----------------------------------------------------------------------------
void FBOMultiSample::bind(const int channel)
{
    glActiveTexture(GL_TEXTURE0+channel);
    glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
}

//-----------------------------------------------------------------------------
// blit
//-----------------------------------------------------------------------------
void FBOMultiSample::blit( FBO *fbo)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FrameBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo->getFrameBuffer());
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

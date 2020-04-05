#include "fbo.h"

#include <iostream>


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
FBO::FBO() : Texture()
{
    m_width = 1280;
    m_height = 720;
    m_format = GL_RGBA;

    //Create texture.
    glGenTextures(1, &m_ColorTextureID);


    glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);



    //Make buffer
    glGenFramebuffers(1, &m_FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

    glGenRenderbuffers(1, &m_DepthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
    #ifdef __WIN32__
    	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
    #else
    	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_width, m_height);
    #endif

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureID, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, m_DepthRenderBuffer);

/*
    GLenum  g_DrawBufferStatusCheck_ENUM = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

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
FBO::~FBO()
{
    glDeleteTextures(1, &m_ColorTextureID);
    glDeleteRenderbuffers(1, &m_DepthRenderBuffer);
    glDeleteFramebuffers(1, &m_FrameBuffer);
}


//-----------------------------------------------------------------------------
// Enable
//-----------------------------------------------------------------------------
void FBO::enable(void)
{
    glGetIntegerv(GL_VIEWPORT, (GLint*)&m_viewport);
    glViewport(0,0,m_width,m_height);

    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}

//-----------------------------------------------------------------------------
// Disable
//-----------------------------------------------------------------------------
void FBO::disable(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,m_viewport[2],m_viewport[3]);
}



//-----------------------------------------------------------------------------
// Set
//-----------------------------------------------------------------------------
void FBO::setSize( int width, int height )
{
    m_width = width;
    m_height = height;


    updateTexture();
}
void FBO::setFormat(GLint format)
{
    m_format = format;
    updateTexture();
}


//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
GLuint FBO::getFrameBuffer(void)
{
    return m_FrameBuffer;
}
GLuint FBO::getColor(void)
{
    return m_ColorTextureID;
}

//-----------------------------------------------------------------------------
// updateTexture
//-----------------------------------------------------------------------------
void FBO::updateTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);


    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

}

//-----------------------------------------------------------------------------
// bind
//-----------------------------------------------------------------------------
void FBO::bind(const int channel)
{
    glActiveTexture(GL_TEXTURE0+channel);
    glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
}

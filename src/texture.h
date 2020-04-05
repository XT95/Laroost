#ifndef TEXTURE_H
#define TEXTURE_H
#ifdef __WIN32__
    #include <GL/glew.h>
#else
    #include <GLES2/gl2.h>
#endif
#include <iostream>



class Texture
{
public:
    Texture();
    ~Texture();

    void load(const std::string &path);
    virtual void bind(const int channel);

    int  getSizeX(){return m_width;}
    int  getSizeY(){return m_height;}
protected:
    GLuint m_id;
    int    m_width,m_height;
};

#endif // TEXTURE_H

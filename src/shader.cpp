#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

#ifndef __WIN32__
    #include <SDL.h>
#endif

//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
Shader::Shader()
{

}
Shader::~Shader()
{

}

//-----------------------------------------------------------------------------
// enable/disable
//-----------------------------------------------------------------------------
void Shader::enable()
{
    glUseProgram(m_program);
}
void Shader::disable()
{
    glUseProgram(0);
}


//-----------------------------------------------------------------------------
// send uniform
//-----------------------------------------------------------------------------
void Shader::send(const char *name, int x)
{
    glUniform1i(glGetUniformLocation(m_program,name), x);
}
void Shader::send(const char *name, int x, int y)
{
    glUniform2i(glGetUniformLocation(m_program,name), x,y);
}
void Shader::send(const char *name, int x, int y, int z)
{
    glUniform3i(glGetUniformLocation(m_program,name), x,y,z);
}
void Shader::send(const char *name, int x, int y, int z, int w)
{
    glUniform4i(glGetUniformLocation(m_program,name), x,y,z,w);
}
void Shader::send(const char *name, float x)
{
	glUniform1f(glGetUniformLocation(m_program,name), x);
}
void Shader::send(const char *name, float x, float y)
{
    glUniform2f(glGetUniformLocation(m_program,name), x,y);
}
void Shader::send(const char *name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(m_program,name), x,y,z);
}
void Shader::send(const char *name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(m_program,name), x,y,z,w);
}
void Shader::send(const char *name, const glm::vec2 &v)
{
    glUniform2fv(glGetUniformLocation(m_program,name), 1, glm::value_ptr(v));
}
void Shader::send(const char *name, const glm::vec3 &v)
{
    glUniform3fv(glGetUniformLocation(m_program,name), 1, glm::value_ptr(v));
}
void Shader::send(const char *name, const glm::vec4 &v)
{
    glUniform4fv(glGetUniformLocation(m_program,name), 1, glm::value_ptr(v));
}
void Shader::send(const char *name, const glm::mat3 &m)
{
    glUniformMatrix3fv(glGetUniformLocation(m_program,name), 1, GL_FALSE, glm::value_ptr(m));
}
void Shader::send(const char *name, const glm::mat4 &m)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program,name), 1, GL_FALSE, glm::value_ptr(m));
}


//-----------------------------------------------------------------------------
// get
//-----------------------------------------------------------------------------
GLuint Shader::getProgramID() const
{
    return m_program;
}

//-----------------------------------------------------------------------------
// load
//-----------------------------------------------------------------------------
bool Shader::load( const char *vertex, const char *geometry, const char *fragment, bool link )
{
    m_program = glCreateProgram();


    if(vertex)
    {
        char *vs = textFileRead(vertex);
        if( !makeShader(vs, GL_VERTEX_SHADER) )
        {
            return false;
        }
        delete[] vs;
    }
    #ifdef __WIN32__
        if(geometry)
        {
            char *gs = textFileRead(geometry);
            if( !makeShader(gs, GL_GEOMETRY_SHADER) )
            {
                return false;
            }
            delete[] gs;
        }
    #endif
    if(fragment)
    {
        char *fs = textFileRead(fragment);
        if( !makeShader(fs, GL_FRAGMENT_SHADER) )
        {
            return false;
        }
        delete[] fs;
    }


    if(link)
        glLinkProgram(m_program);

    return true;
}
void Shader::link()
{
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };
    glLinkProgram(m_program);

    glGetProgramiv(m_program, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(m_program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return;
    }

    glValidateProgram(m_program);
    glGetProgramiv(m_program, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(m_program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
     //   return false;
    }

}

bool Shader::makeShader(const char *txt, GLuint type)
{
    GLuint object = glCreateShader(type);
	glShaderSource(object, 1, (const GLchar**)(&txt), NULL);
	glCompileShader(object);
	
    if( checkShader(object) )
    {
        glAttachShader(m_program, object);
        glDeleteShader(object);
    }
    else
    {
        std::cout << txt << std::endl;
        if(type == GL_VERTEX_SHADER)
            std::cout << "vertex shader" << std::endl;
        #ifdef __WIN32__
            else if(type == GL_GEOMETRY_SHADER)
                std::cout << "geometry shader" << std::endl;
        #endif
        else if(type == GL_FRAGMENT_SHADER)
            std::cout << "fragment shader" << std::endl;
        return false;
    }
    return true;
}

bool Shader::checkShader(int id)
{
    GLint ok = 0;

    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if( ok != GL_TRUE )
    {
        GLint logLength = 0;
        GLchar* log = NULL;

        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        log = new GLchar[logLength];
        glGetShaderInfoLog(id, logLength, &logLength, log);

        std::cout << "Shader error :" << log << std::endl;

        delete[] log;

        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
// Read File
//-----------------------------------------------------------------------------
char* Shader::textFileRead(const char *fn)
{
    #ifdef __WIN32__
        std::ifstream file(fn, std::ios::in | std::ios::binary);

        std::string str( (std::istreambuf_iterator<char>( file )),
                       (std::istreambuf_iterator<char>()) );

        file.close();

        char* data = new char[str.length() + 1];
        memset(data, 0x00, str.length() + 1);
        memcpy(data, str.c_str(), str.length());
        data[str.length()] = '\0';
    #else
        SDL_RWops *file;
        file = SDL_RWFromFile(fn, "r");
        if(!file)
        {
            SDL_Log( "Can't read %s\n", fn);
            return NULL;
        }

        size_t length = SDL_RWseek(file, 0, SEEK_END);
        char* data = new char[length + 1];
        memset(data, 0x00, length + 1);

        SDL_RWseek(file, 0, SEEK_SET);
        int n_blocks = SDL_RWread(file, (data), 1, length);
        SDL_RWclose(file);
        data[length] = '\0';
        //SDL_Log( "%s\n", data);
    #endif
    return data;
}








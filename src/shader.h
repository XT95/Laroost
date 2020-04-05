#ifndef DEF_SHADER
#define DEF_SHADER

#ifdef __WIN32__
    #include <GL/glew.h>
#else
    #include <GLES2/gl2.h>
#endif
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();
	
    bool load(const char *vertex, const char *geometry, const char *fragment, bool link = true);
    void link();

	void enable();
	void disable();

    void send(const char *name, int x);
    void send(const char *name, int x, int y);
    void send(const char *name, int x, int y, int z);
    void send(const char *name, int x, int y, int z, int w);
    void send(const char *name, float x);
    void send(const char *name, float x, float y);
    void send(const char *name, float x, float y, float z);
    void send(const char *name, float x, float y, float z, float w);
    void send(const char *name, const glm::vec3 &v);
    void send(const char *name, const glm::vec2 &v);
    void send(const char *name, const glm::vec4 &v);
    void send(const char *name, const glm::mat3 &m);
    void send(const char *name, const glm::mat4 &m);

    GLuint getProgramID() const;

private:
    bool makeShader(const char *txt, GLuint type);
    bool checkShader( int id );
    char* textFileRead(const char *fn);
	GLuint m_program;
};



#endif

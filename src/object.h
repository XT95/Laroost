#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "geometry.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

class Object
{
public:
    Object();
    Object(const Object &obj);
    ~Object();

    Object& operator=(Object const& obj);

    virtual void draw(Camera &cam);

    //Accessors
    void setGeometry(Geometry *geo);
    void setShader( Shader &shad);
    void setShader( const char *vertex, const char*fragment);
    void setTexture( Texture &tex );
    void setTexture( const char *filename );
    void setTransform( glm::mat4 &mat);
    void setShow(bool a);

    bool getShow();
    Geometry* getGeometry();
    Shader& getShader();
    Texture& getTexture();
    glm::mat4& getTransform();

protected:
    Geometry *m_geo;
    Shader m_shad;
    Texture m_tex;
    glm::mat4 m_transform;
    bool m_display;
};

#endif // OBJECT_H

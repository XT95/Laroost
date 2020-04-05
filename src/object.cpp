#include "core.h"
#include "object.h"

Object::Object()
{
    m_geo = NULL;
    m_transform = glm::mat4(1.f);
}
Object::Object(const Object &obj)
{
    m_geo = obj.m_geo;
    m_shad = obj.m_shad;
    m_tex = obj.m_tex;
    m_transform = obj.m_transform;
    m_display = true;
}

Object::~Object()
{
    delete m_geo;
}

Object& Object::operator =(const Object &obj)
{

    m_geo = obj.m_geo;
    m_shad = obj.m_shad;
    m_tex = obj.m_tex;
    m_transform = obj.m_transform;

    return *this;
}

void Object::draw(Camera &cam)
{
    if(m_display)
    {
        m_tex.bind(0);
        m_shad.enable();

        m_shad.send("texture0",0);
        m_shad.send("level",Core::instance().level);
        m_shad.send("speed",Core::instance().speed);
        m_shad.send("time",Core::instance().time);
        m_shad.send("modelViewMatrix", cam.getViewMatrix() * m_transform);
        m_shad.send("projectionMatrix", cam.getProjectionMatrix());

        if(m_geo)
            m_geo->draw();

        m_shad.disable();
    }
}


//Accessors
void Object::setGeometry( Geometry *geo)
{
    m_geo = geo;
}

void Object::setShader( Shader &shad)
{
    m_shad = shad;
}
void Object::setShader( const char *vertex, const char*fragment)
{
    m_shad.load(vertex, NULL, fragment);
}

void Object::setTexture( const char *filename)
{
    m_tex.load(filename);
}
void Object::setTexture( Texture &tex)
{
    m_tex = tex;
}

void Object::setTransform( glm::mat4 &mat)
{
    m_transform = mat;
}
void Object::setShow(bool a)
{
    m_display = a;
}

Geometry* Object::getGeometry()
{
    return m_geo;
}

Shader& Object::getShader()
{
    return m_shad;
}

Texture& Object::Object::getTexture()
{
    return m_tex;
}

glm::mat4& Object::getTransform()
{
    return m_transform;
}
bool Object::getShow()
{
    return m_display;
}

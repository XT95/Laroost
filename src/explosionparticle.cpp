#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cubegeometry.h"
#include "explosionparticle.h"

inline float randf()
{
    return float(rand())/RAND_MAX;
}
inline float srandf()
{
    return float(rand())/RAND_MAX*2.f-1.f;
}

ExplosionParticle::ExplosionParticle()
{
    m_geo = new CubeGeometry();
    setShader("Data/Shaders/reactor.vsh", "Data/Shaders/reactor.fsh");

    reset();
    m_life = 0.f;
    m_time = 0.f;
}

ExplosionParticle::~ExplosionParticle()
{

}

void ExplosionParticle::reset()
{
    m_life = 1.f;
    for(int i=0; i<100; i++)
    {
        m_parts[i].life = randf();
        m_parts[i].pos = glm::vec3(srandf()*.25f,srandf()*.25f+1.f,-21.f+randf()*20.f);
        m_parts[i].rot = glm::vec3(srandf(),srandf(),srandf());
        m_parts[i].vel = glm::vec3(srandf(),srandf(),srandf())*srandf()*10.f;
    }

}

void ExplosionParticle::hide()
{
    m_life = 0.f;

}

void ExplosionParticle::update(float elapsed, float offset)
{
    m_life -= elapsed*.1;
    if(m_life>0.)
    {
        m_time += elapsed;
        for(int i=0; i<100; i++)
        {
            m_parts[i].pos += m_parts[i].vel*elapsed;
            m_parts[i].life -= elapsed;
        }
    }
}

void ExplosionParticle::draw(Camera &cam)
{
    if(!m_display)
        return;

    if(m_life>0.)
    {
        //Draw cube
        m_tex.bind(0);
        m_shad.enable();
        m_shad.send("projectionMatrix", cam.getProjectionMatrix());

        for(int i=0; i<100; i++)
        {
            m_transform = glm::translate(glm::mat4(1.f), m_parts[i].pos);
            m_transform = glm::rotate(m_transform, m_time*2.f, m_parts[i].rot);
            m_transform = glm::scale(m_transform, glm::vec3(.5f-fmax(m_parts[i].life,0.f)*.35f));
            m_shad.send("modelViewMatrix", cam.getViewMatrix() * m_transform);
            m_shad.send("life", m_parts[i].life);
            m_shad.send("id", (float)i/100.f*50.f);

            m_geo->draw();
        }
        m_shad.disable();
    }
}

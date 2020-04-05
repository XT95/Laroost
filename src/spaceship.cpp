#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "spaceship.h"
#include "spaceshipgeometry.h"
#include "planegeometry.h"

Spaceship::Spaceship()
{
    setGeometry(new SpaceshipGeometry());
    setShader("Data/Shaders/spaceship.vsh", "Data/Shaders/spaceship.fsh");
    setTexture("Data/Imgs/cube.png");
    glm::mat4 mat = glm::translate(glm::mat4(1.f), glm::vec3(0.,1.,-20.));
    setTransform(mat);

    //Shadow
    m_shadow.setGeometry(new PlaneGeometry(1.f));
    mat[3][1] = 0.1f;
    m_shadow.setTransform(mat);
    m_shadow.setShader("Data/Shaders/shadow.vsh", "Data/Shaders/shadow.fsh");
    m_shadow.setTexture("Data/Imgs/shipShad.png");
}

Spaceship::~Spaceship()
{

}

void Spaceship::update( float elapsed, float offset )
{
    if(m_display)
    {
        m_transform = glm::rotate( glm::translate(glm::mat4(1.f), glm::vec3(0.,1.,-20.)), offset*28.f, glm::vec3(0.,0.,1.) );
        m_reactor.update(elapsed,offset);
    }
}

void Spaceship::draw(Camera &cam)
{
    if(!m_display)
        return;

    Object::draw(cam);
    m_reactor.draw(cam);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    m_shadow.draw(cam);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

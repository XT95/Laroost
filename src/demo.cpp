#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core.h"
#include "demo.h"
#include "cubegeometry.h"
#include "planegeometry.h"
#include "spaceshipgeometry.h"

Demo::Demo(int width, int height) :
    m_graphic(glm::ivec2(width,height)),
    m_menu(glm::ivec2(width,height))
{
    Core::instance().init();
    m_map = new Map();
    m_spaceship = new Spaceship();
    m_explosion = new ExplosionParticle();

    m_offset = 0.f;
}

Demo::~Demo()
{

}

void Demo::init()
{
    Core::instance().reset();

    //Ground
    Object *obj = new Object();
    obj->setGeometry(new PlaneGeometry(1000));
    obj->setShader("Data/Shaders/plane.vsh", "Data/Shaders/plane.fsh");
    obj->setTexture("Data/Imgs/cube.png");
    m_graphic.addObject(obj);

    //Spaceship
    m_graphic.addObject(m_spaceship);

    //Explosion particle
    m_graphic.addObject(m_explosion);

    //Cube field
    m_graphic.addObject(m_map);

    m_menu.update();
}
void Demo::resize(int width, int height)
{
    m_graphic.resize(glm::ivec2(width,height));
}

void Demo::update(const float elapsed, int control, bool space)
{
    Core::instance().update(elapsed);
    m_explosion->update(elapsed, m_offset);

    //Control
    m_offset -= float(control)*elapsed*.1;
    m_offset = fmax(m_offset,-0.09);
    m_offset = fmin(m_offset,0.09);

    m_offset -= m_offset*.05;
    Core::instance().offset = m_offset;

    switch(Core::instance().mode)
    {
        case CORE_MENU:
            m_explosion->hide();
            m_map->update(elapsed, 0.);
            Core::instance().level = 0;
            Core::instance().speed = 50;
            if(space)
            {
                m_map->reset();
                Core::instance().play();
                m_spaceship->setShow(true);
                m_explosion->setShow(false);
            }
        break;
        case CORE_PLAYING:
            m_spaceship->update(elapsed, m_offset);
            m_map->update(elapsed, m_offset);
            if(m_map->collision())
            {
                Core::instance().mode = CORE_GAMEOVER;
                Core::instance().speed = 0.;
                m_explosion->setShow(true);
                m_spaceship->setShow(false);
                m_explosion->reset();
                //m_map->reset();
            }
        break;
        case CORE_GAMEOVER:
            Core::instance().fade -= elapsed*.5;
            if(Core::instance().fade<0.)
            {
                Core::instance().updateScore();
                m_menu.update();
                Core::instance().reset();
                Core::instance().mode = CORE_MENU;
            }
        break;
    }


}

void Demo::render()
{
    if(Core::instance().mode == CORE_MENU)
    {
        m_spaceship->setShow(false);
        m_graphic.getCamera().getViewMatrix() = glm::translate(glm::mat4(1.f), glm::vec3(0.,-5.,5.));
        m_menu.draw(&m_graphic);
    }
    else
    {
        m_spaceship->setShow(true);
        m_graphic.getCamera().getViewMatrix() = glm::rotate( glm::translate(glm::mat4(1.f), glm::vec3(0.,-5.,5.)), -m_offset*15.5f, glm::vec3(0.,0.,1.));
        m_graphic.draw();
    }
}

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "core.h"
#include "map.h"
#include "cubegeometry.h"
#include "planegeometry.h"

Map::Map() : Object()
{
    m_geo = new CubeGeometry();
    setShader("Data/Shaders/cube.vsh", "Data/Shaders/cube.fsh");
    setTexture("Data/Imgs/cube.png");


    m_shadowGeo = new PlaneGeometry(5.);
    m_shadowShader.load("Data/Shaders/shadow.vsh",NULL,"Data/Shaders/shadow.fsh");
    m_shadowTexture.load("Data/Imgs/cubeShad.png");

    reset();
}

Map::~Map()
{

}

bool Map::collision()
{
    return m_collide;
}

void Map::reset()
{

    for(int i=0; i<200; i++)
    {
        m_pos[i].x = rand()%150-75;
        m_pos[i].y = 1.f;
        m_pos[i].z = 0.;
    }

    m_stateProgress = 0;
    m_time = 0.f;
    m_stateX = 0.f;
    m_stateZ = 0.f;
    endAt = -150.;
    m_startLevel = 0;
    m_state = BSTART;
    m_collide = false;
}



void Map::buildRandom()
{

    for(int i=0; i<200; i++)
    {
        //Respawn
        if(m_pos[i].z > -10.f)
        {

            m_pos[i].x = rand()%150-75;
            m_pos[i].z = endAt + m_stateZ - m_stateProgress*300/200;


            m_stateProgress++;

            if(m_stateProgress > 400)
            {
                endAt = endAt + m_stateZ - 650 ;
                m_stateProgress = -1.;
                m_stateX = 0.;
                m_stateZ = 0.;
                return;
            }
        }
    }
}

void Map::buildIntroTunnel()
{

    for(int i=0; i<200; i++)
    {
        //Respawn
        if(m_pos[i].z > -10.f)
        {

            if(m_stateProgress < 60) //Wall
            {
                m_pos[i].x = pow((double)-1,(double)m_stateProgress)*(15+m_stateProgress) + m_stateX;
                m_pos[i].z = endAt + m_stateZ;
            }
            else //Tunnel
            {
                float a = (m_stateProgress-60)/50.;
                m_pos[i].x = pow((double)-1,(double)m_stateProgress)*(15 - (1.-exp(-a*10.))*7. ) + m_stateX;
                m_pos[i].z = endAt + m_stateZ - (m_stateProgress-60);
            }



            m_stateProgress++;

            if(m_stateProgress > 110)
            {
                endAt = endAt + m_stateZ - (m_stateProgress-60);
                m_stateProgress = -1.;
                m_stateZ = 0.;
                return;
            }
        }
    }
}


void Map::buildSnake()
{

    for(int i=0; i<200; i++)
    {
        //Respawn
        if(m_pos[i].z > -10.f)
        {

            float a = ((float)m_stateProgress)/200.;
            m_pos[i].x = pow((double)-1,(double)m_stateProgress)*8 + (cos(a*5.)-1.)*25. + m_stateX;
            m_pos[i].z = endAt + m_stateZ - m_stateProgress;


            m_stateProgress++;

            if(a > 4.)
            {
                endAt = endAt + m_stateZ - m_stateProgress-50;
                m_stateX = 0.;
                m_stateZ = 0.;
                m_stateProgress = -1.;
                return;
            }
        }
    }
}

void Map::buildCrossing()
{
    const float velocity = 1.7;
    for(int i=0; i<200; i++)
    {
        //Respawn
        if(m_pos[i].z > -10.f)
        {

            if(m_stateProgress < 20 )
            {
                m_pos[i].x = pow((double)-1,(double)m_stateProgress)*(8+m_stateProgress) + m_stateX;
                m_pos[i].z = endAt + m_stateZ - m_stateProgress*velocity;
            }
            else if(m_stateProgress < 40 )
            {
                m_pos[i].x = pow((double)-1,(double)m_stateProgress)*(8-m_stateProgress+40) + m_stateX;
                m_pos[i].z = endAt + m_stateZ - m_stateProgress*velocity;
            }
            else if(m_stateProgress < 48 )
            {
                m_pos[i].x = pow((double)-1,(double)m_stateProgress)*(m_stateProgress-40) + m_stateX;
                m_pos[i].z = endAt + m_stateZ - (float)(m_stateProgress-30)*velocity;
            }
            else if(m_stateProgress < 56 )
            {
                m_pos[i].x = pow((double)-1,(double)m_stateProgress)*(8-(m_stateProgress-47)) + m_stateX;
                m_pos[i].z = endAt + m_stateZ - (float)(m_stateProgress-30)*velocity;
            }

            m_stateProgress++;

            if(m_stateProgress > 56 )
            {
                m_crossingID++;
                endAt = endAt + m_stateZ - m_stateProgress-5;
                m_stateProgress = 0.;
                m_stateZ = 0.;
                if(m_crossingID == 3)
                {
                    endAt -= 25;
                    m_stateX = 0.;
                    m_stateProgress = -1.;
                    return;
                }
            }
        }
    }
}
void Map::buildStartTunnel()
{

    for(int i=0; i<200; i++)
    {
        //Respawn
        if(m_pos[i].z > -10.f)
        {

            m_pos[i].x = pow((double)-1,(double)m_stateProgress)*8 + m_stateX;
            m_pos[i].z = endAt + m_stateZ - m_stateProgress;


            m_stateProgress++;

            if(m_stateProgress > 50 )
            {
                endAt = endAt + m_stateZ - m_stateProgress-50;
                m_stateProgress = -1.;
                m_stateX = 0.;
                m_stateZ = 0.;
                return;
            }
        }
    }
}

void Map::update(float elapsed, float offset)
{
    //Change & init states !
    m_time += elapsed;


    m_stateZ += elapsed*Core::instance().speed;
    m_stateX += offset*30.f;

    //Level Up
    float last = m_startLevel;
    m_startLevel += elapsed*Core::instance().speed;
    Core::instance().showSpeedUp = m_startLevel > -3.*Core::instance().speed && m_startLevel<0.;
    if( m_startLevel > 0. && last <= 0.)
    {
        Core::instance().speed += 10;
        Core::instance().level = (Core::instance().level+1)%3;
    }

    //Build world in live.. :)
    switch(m_state)
    {
    case BSTART:
        buildIntroTunnel();
        if(m_stateProgress == -1)
        {
            m_state = START;
            m_stateProgress = 0;
        }
    break;
    case START:
        buildStartTunnel();
        if(m_stateProgress == -1)
        {
            m_state = RANDOM1;
            m_stateProgress = 0;
        }
    break;



    case RANDOM1:
        buildRandom();
        if(m_stateProgress == -1)
        {
            m_state = BCROSSING;
            m_stateProgress=0;
        }
    break;

    case BCROSSING:
        buildIntroTunnel();
        if(m_stateProgress == -1)
        {
            m_state = CROSSING;
            m_crossingID = 0;
            m_stateProgress=0;
        }
    break;
    case CROSSING:
        buildCrossing();
        if(m_stateProgress == -1)
        {
            m_state = RANDOM2;
            m_stateProgress=0;
        }
    break;


    case RANDOM2:
        buildRandom();
        if(m_stateProgress == -1)
        {
            m_state = BSNAKE;
            m_stateProgress=0;
        }
    break;


    case BSNAKE:
        buildIntroTunnel();
        if(m_stateProgress == -1)
        {
            m_state = SNAKE;
            m_stateProgress=0;
        }
    break;
    case SNAKE:
        buildSnake();
        if(m_stateProgress == -1)
        {
            m_state = RANDOM3;
            m_stateProgress=0;
        }
    break;

    case RANDOM3:
        buildRandom();
        if(m_stateProgress == -1)
        {
            m_state = BSTART;
            m_stateProgress=0;
            m_startLevel = endAt;
        }
    break;

    }


    //For each cubes
    for(int i=0; i<200; i++)
    {
        //Move
        m_pos[i].z += elapsed*Core::instance().speed;
        m_pos[i].x += offset*30.f;

        //Check X limits
        if(m_pos[i].x>75.f)
            m_pos[i].x -= 150.f;
        else if(m_pos[i].x<-75.f)
            m_pos[i].x += 150.f;

        //Check collision
        if(fabs(m_pos[i].x)<1.5 && fabs(m_pos[i].z+21.)<1.)
            m_collide = true;
    }
}


void Map::draw( Camera &cam )
{
    //Draw cube
    m_tex.bind(0);
    m_shad.enable();
    m_shad.send("projectionMatrix", cam.getProjectionMatrix());

    for(int i=0; i<200; i++)
    {
        m_transform = glm::translate(glm::mat4(1.f), m_pos[i]);
        m_shad.send("modelViewMatrix", cam.getViewMatrix() * m_transform);
        m_shad.send("id", (float)i/100.f*50.f);
        m_shad.send("level", Core::instance().level);

        m_geo->draw();
    }
    m_shad.disable();


    //Draw shadow
    m_shadowTexture.bind(0);
    m_shadowShader.enable();
    m_shadowShader.send("projectionMatrix", cam.getProjectionMatrix());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    for(int i=0; i<200; i++)
    {
        m_transform = glm::translate(glm::mat4(1.f), m_pos[i]);
        m_transform[3][1] -= .95f;
        m_shadowShader.send("modelViewMatrix", cam.getViewMatrix() * m_transform);
        m_shadowShader.send("id", (float)i/100.f*50.f);
        m_shadowShader.send("level", Core::instance().level);

        m_shadowGeo->draw();
    }
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    m_shadowShader.disable();
}

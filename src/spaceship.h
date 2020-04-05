#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "camera.h"
#include "reactorparticle.h"
#include "object.h"


class Spaceship : public Object
{
public:
    Spaceship();
    ~Spaceship();

    void update(float elapsed , float offset);
    void draw( Camera &cam);
protected:
    Object m_shadow;
    ReactorParticle m_reactor;
};

#endif // SPACESHIP_H

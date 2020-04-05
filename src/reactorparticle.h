#ifndef REACTORPARTICLE_H
#define REACTORPARTICLE_H

#include <glm/glm.hpp>
#include "object.h"

struct ReactorPart
{
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 rot;
    float life;
};

class ReactorParticle : public Object
{
public:
    ReactorParticle();
    ~ReactorParticle();

    void update(float elapsed, float offset);
    void draw(Camera &cam);
protected:
    ReactorPart m_parts[100];
    float m_time;
};

#endif // REACTORPARTICLE_H

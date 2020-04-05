#ifndef ExplosionParticle_H
#define ExplosionParticle_H

#include <glm/glm.hpp>
#include "object.h"

struct ExplosionPart
{
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 rot;
    float life;
};

class ExplosionParticle : public Object
{
public:
    ExplosionParticle();
    ~ExplosionParticle();

    void hide();
    void reset();
    void update(float elapsed, float offset);
    void draw(Camera &cam);
protected:
    ExplosionPart m_parts[100];
    float m_time;
    float m_life;
};

#endif // ExplosionParticle_H

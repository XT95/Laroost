#ifndef DEMO_H
#define DEMO_H

#include <map>
#include <glm/glm.hpp>
#include "graphicengine.h"
#include "map.h"
#include "spaceship.h"
#include "explosionparticle.h"
#include "text.h"
#include "menu.h"

class Demo
{
public:
    Demo(int width, int height);
    ~Demo();
    void init();
    void reset();

    void resize(int width, int height);
    void update(const float elapsed, int control , bool space);

    void render();

private:
    Menu m_menu;
    GraphicEngine m_graphic;
    Map *m_map;
    Spaceship *m_spaceship;
    ExplosionParticle *m_explosion;

    float m_offset;
};

#endif // DEMO_H

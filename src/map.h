#ifndef MAP_H
#define MAP_H

#include <glm/glm.hpp>
#include "object.h"

enum LevelState { RANDOM1, RANDOM2, RANDOM3, SNAKE, CROSSING, START, BSTART, BSNAKE, BCROSSING};

class Map : public Object
{
public:
    Map();
    ~Map();

    void reset();
    bool collision();

    void update(float elapsed, float offset);
    void draw(Camera &cam);
protected:
    void buildIntroTunnel();
    void buildStartTunnel();
    void buildSnake();
    void buildRandom();
    void buildCrossing();

    glm::vec3 m_pos[200];
    Geometry *m_shadowGeo;
    Shader m_shadowShader;
    Texture m_shadowTexture;
    int m_crossingID;
    LevelState m_state;
    int m_stateProgress;
    float m_startLevel;
    float m_stateZ,m_stateX;
    float endAt;
    float m_time;
    bool m_collide;
};

#endif // MAP_H

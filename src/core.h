#ifndef CORE_H
#define CORE_H

#include "shader.h"
#include "texture.h"

#define CORE_MENU 0
#define CORE_PLAYING 1
#define CORE_GAMEOVER 2

class Core
{
public:
    static Core& instance();

    int mode;
    float score;
    float highscore;
    float rank;
    int level;
    float speed;
    float time;
    float offset;
    float fade;
    Texture font;
    Shader  shaderText;
    bool showSpeedUp;

    void init();
    void updateScore();
    void update(float elapsed);
    void play();
    void reset();
private:
    Core();
    ~Core();
    static Core m_instance;
};

#endif // CORE_H

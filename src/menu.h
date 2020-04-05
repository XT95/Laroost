#ifndef MENU_H
#define MENU_H


#include <vector>
#include <glm/glm.hpp>

#include "object.h"
#include "shader.h"
#include "camera.h"
#include "fbo.h"
#include "text.h"
#include "sprite.h"
#include "graphicengine.h"

class Menu
{
public:
    Menu( glm::ivec2 screen );
    ~Menu();

    void update();
    void draw(GraphicEngine *graph);


protected:
    Text m_title;
    Text m_scoreLabel;
    Text m_highscoreLabel;
    Text m_rankLabel;
    Text m_score;
    Text m_highscore;
    Text m_rank;

    Text m_play;

    Text m_scroller;

    Shader m_finalFX;
    FBO m_fbo;
    FBO m_fboScene,m_fboScene2;
    Shader m_blur;
    bool m_showScore;
    Sprite m_logo;
};

#endif // MENU_H

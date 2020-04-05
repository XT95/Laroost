#include "fast2dquad.h"
#include "graphicengine.h"
#include "core.h"

GraphicEngine::GraphicEngine(glm::ivec2 screenSize)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.,.0,.0,1.);

    Fast2DQuad::instance().init();
    #ifdef __WIN32__
        m_fboMS.setSize(screenSize.x, screenSize.y);
    #endif
    m_fbo.setSize(screenSize.x, screenSize.y);
    m_fboFinal.setSize(screenSize.x, screenSize.y);

    m_backgroundShad.load("Data/Shaders/background.vsh", NULL, "Data/Shaders/background.fsh");
    m_postFX.load("Data/Shaders/postFX.vsh", NULL, "Data/Shaders/postFX.fsh");
    m_postFX.send("tex",0);

    m_finalFX.load("Data/Shaders/finalFX.vsh", NULL, "Data/Shaders/finalFX.fsh");
    m_finalFX.send("tex",0);

    m_score.setSize(1./42.);
    m_score.setPosition(glm::vec2(-.9,.9));

    m_levelup.setSize(1./32.);
    m_levelup.setPosition(glm::vec2(-.25,0.8));
    m_levelup.setText("Level Up");
    m_speedup.setSize(1./32.);
    m_speedup.setPosition(glm::vec2(-.25,0.8));
    m_speedup.setText("Speed Up");
}

GraphicEngine::~GraphicEngine()
{
    Fast2DQuad::instance().free();
    for(int i=0; i<m_objs.size(); i++)
        if(m_objs[i])
            delete m_objs[i];
}

void GraphicEngine::resize(glm::ivec2 screenSize)
{
    glViewport(0, 0, screenSize.x, screenSize.y);
    #ifdef __WIN32__
        m_fboMS.setSize(screenSize.x, screenSize.y);
    #endif
    m_fbo.setSize(screenSize.x, screenSize.y);
}

//Objects accessors
void GraphicEngine::addObject( Object *obj )
{
    m_objs.push_back(obj);
}

void GraphicEngine::removeObject( Object *obj )
{

}

//Camera transform
void GraphicEngine::setCamera( Camera &camera )
{
    m_cam = camera;
}
Camera& GraphicEngine::getCamera()
{
    return m_cam;
}

//Draw
void GraphicEngine::draw()
{
    //Draw the game with AA

    #ifdef __WIN32__
        m_fboMS.enable();
    #else
        m_fbo.enable();
    #endif
        
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw background
        glDisable(GL_DEPTH_TEST);
        m_backgroundShad.enable();
        m_backgroundShad.send("level", Core::instance().level);
        m_backgroundShad.send("offset", Core::instance().offset);
        Fast2DQuad::instance().render();
        m_backgroundShad.disable();
        glEnable(GL_DEPTH_TEST);

        //Draw scene
        for(int i=0; i<m_objs.size(); i++)
            m_objs[i]->draw(m_cam);

    #ifdef __WIN32__
        m_fboMS.disable();
        m_fboMS.blit(&m_fbo);
    #else
        m_fbo.disable();
    #endif

    //Post processing + text
    m_fboFinal.enable();
        glClear( GL_DEPTH_BUFFER_BIT);
        m_postFX.enable();
            m_fbo.bind(0);
            Fast2DQuad::instance().render();
        m_postFX.disable();

        if( Core::instance().showSpeedUp && (int)(Core::instance().time*3.)%2==1 && Core::instance().level>-1)
            m_speedup.draw();

        char tmp[10];
        sprintf(tmp, "%d\0", (int)Core::instance().score);
        m_score.setText(std::string(tmp));
        m_score.draw();
    m_fboFinal.disable();

    //Final rendering
    glClear( GL_DEPTH_BUFFER_BIT);
    m_finalFX.enable();
        m_finalFX.send("fade", (float)fmax( fmin( Core::instance().time,1.)*Core::instance().fade, 0.));
        m_fboFinal.bind(0);
        Fast2DQuad::instance().render();
    m_finalFX.disable();
}

//Draw for demo
void GraphicEngine::drawForMenu()
{
    //Draw background
    glDisable(GL_DEPTH_TEST);
    m_backgroundShad.enable();
    m_backgroundShad.send("level", Core::instance().level);
    m_backgroundShad.send("offset", 0.f);
    Fast2DQuad::instance().render();
    m_backgroundShad.disable();
    glEnable(GL_DEPTH_TEST);

    //Draw scene
    for(int i=0; i<m_objs.size(); i++)
        m_objs[i]->draw(m_cam);
}

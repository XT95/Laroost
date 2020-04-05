#include "core.h"
#include "fast2dquad.h"
#include "menu.h"

Menu::Menu( glm::ivec2 screen )
{
    m_showScore = false;
    m_fboScene.setSize(256,144);
    m_fboScene2.setSize(256,144);

    m_fbo.setSize(screen.x, screen.y);

    m_blur.load("Data/Shaders/blur.vsh", NULL, "Data/Shaders/blur.fsh");
    m_blur.send("tex",0);

    m_finalFX.load("Data/Shaders/finalFX.vsh", NULL, "Data/Shaders/finalFX.fsh");
    m_finalFX.send("tex",0);

    m_logo.setTexture("Data/Imgs/logo.png");
    m_logo.setShader("Data/Shaders/sprite.vsh","Data/Shaders/sprite.fsh");
    m_logo.setSize( glm::vec2(.15/16.*9.,.15) );
    m_logo.setPosition( glm::vec2(-.35,.8) );

    m_title.setSize(1./20.);
    m_title.setPosition(glm::vec2(-.19,.75));
    m_title.setText("Laroost\0");

    m_scoreLabel.setPosition(glm::vec2(-.45,.2));
    m_scoreLabel.setText("Score\0");

    m_score.setPosition(glm::vec2(.2,.2));

    m_highscoreLabel.setPosition(glm::vec2(-.445,.1));
    m_highscoreLabel.setText("Highscore\0");

    m_highscore.setPosition(glm::vec2(.2,.1));

    m_rankLabel.setPosition(glm::vec2(-.45,0.));
    m_rankLabel.setText("Rank\0");

    m_rank.setPosition(glm::vec2(.2,.0));


    m_play.setPosition(glm::vec2(-.55,-.4));
    m_play.setText("Press space to play\0");


    m_scroller.setPosition(glm::vec2(0.,-0.8));
    m_scroller.setShader("Data/Shaders/scrolltext.vsh", "Data/Shaders/scrolltext.fsh");
    m_scroller.setText("Another clone of Cube Field made with <3   --   Original game by Max Abernethy    --  Code by Anatole Duprat   --  Music by Nicolas Allemand  --  Enjoy :)  --   Yes, that's a scroll text like back to the old days... but in worst !!    --   Why are you still on this screen ?!                    Just tap on the screen ;) NAHABOOOOOOOOOOOOOOOOO\0");

}

Menu::~Menu()
{

}

void Menu::update()
{

    m_showScore = (int)Core::instance().score>0;
    char tmp[20];

    sprintf(tmp, "%d", (int)Core::instance().score);
    for(int i=1; i<5; i++)
        if( (int)Core::instance().score < pow(10.,(double)i) )
        {
            for(int j=18; j>=0; j--)
                tmp[j+1] = tmp[j];
            tmp[0] = ' ';
        }
    m_score.setText(std::string(tmp));

    sprintf(tmp, "%d", (int)Core::instance().highscore);
    for(int i=1; i<5; i++)
        if( (int)Core::instance().highscore < pow(10.,(double)i) )
        {
            for(int j=18; j>=0; j--)
                tmp[j+1] = tmp[j];
            tmp[0] = ' ';
        }
    m_highscore.setText(std::string(tmp));

    sprintf(tmp, "%d", (int)Core::instance().rank);
    for(int i=1; i<5; i++)
        if( (int)Core::instance().rank < pow(10.,(double)i) )
        {
            for(int j=18; j>=0; j--)
                tmp[j+1] = tmp[j];
            tmp[0] = ' ';
        }
    m_rank.setText(std::string(tmp));


}


void Menu::draw(GraphicEngine *graph)
{
    //Render the map
    m_fboScene.enable();
        glClear(GL_DEPTH_BUFFER_BIT);
        graph->drawForMenu();
    m_fboScene.disable();

    //Horizontal blur
    m_fboScene2.enable();
        glClear(GL_DEPTH_BUFFER_BIT);
        m_blur.enable();
            m_blur.send("offset", glm::vec2(1.f/256.f,0.f) );
            m_fboScene.bind(0);
            Fast2DQuad::instance().render();
        m_blur.disable();
    m_fboScene2.disable();

    //Draw menu
    m_fbo.enable();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //Vertical blur
        m_blur.enable();
            m_blur.send("offset", glm::vec2(0.f,1.f/144.f) );
            m_fboScene2.bind(0);
            Fast2DQuad::instance().render();
        m_blur.disable();

        m_logo.draw();
        m_title.draw();

        if(m_showScore)
        {
            m_scoreLabel.draw(); m_score.draw();
        }
        m_highscoreLabel.draw(); m_highscore.draw();
        m_rankLabel.draw(); m_rank.draw();

        m_play.draw();

        m_scroller.draw();
    m_fbo.disable();

    //Final rendering
    glClear( GL_DEPTH_BUFFER_BIT);
    m_finalFX.enable();
        m_finalFX.send("fade", (float)fmin( Core::instance().time,1.));
        m_fbo.bind(0);
        Fast2DQuad::instance().render();
    m_finalFX.disable();

}

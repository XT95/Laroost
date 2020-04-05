#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include <vector>
#include <glm/glm.hpp>

#include "object.h"
#include "shader.h"
#include "camera.h"
#include "fbo.h"
#include "text.h"
#include "fbomultisample.h"

class GraphicEngine
{
public:
    GraphicEngine(glm::ivec2 screenSize);
    ~GraphicEngine();

    void resize( glm::ivec2 screenSize);

    //Objects accessors
    void addObject( Object *obj );
    void removeObject(Object *obj );

    //Camera transform
    void setCamera( Camera &camera );
    Camera& getCamera();


    //Draw
    void draw();
    void drawForMenu();

protected:
    std::vector<Object*> m_objs;
    Camera m_cam;
    #ifdef __WIN32__
        FBOMultiSample m_fboMS;
    #endif
    FBO m_fbo;
    FBO m_fboFinal;

    Shader m_postFX;
    Shader m_finalFX;
    Shader m_backgroundShad;

    Text m_score;
    Text m_levelup;
    Text m_speedup;
};

#endif // GRAPHICENGINE_H

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lgdi32 -mwindows

SOURCES += main.cpp \
    demo.cpp \
    fast2dquad.cpp \
    fbo.cpp \
    shader.cpp \
    texture.cpp \
    graphicengine.cpp \
    geometry.cpp \
    object.cpp \
    camera.cpp \
    cubegeometry.cpp \
    map.cpp \
    planegeometry.cpp \
    spaceshipgeometry.cpp \
    reactorparticle.cpp \
    spaceship.cpp \
    core.cpp \
    explosionparticle.cpp \
    text.cpp \
    menu.cpp \
    fbomultisample.cpp \
    sprite.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    demo.h \
    fast2dquad.h \
    fbo.h \
    shader.h \
    texture.h \
    graphicengine.h \
    geometry.h \
    object.h \
    camera.h \
    cubegeometry.h \
    map.h \
    planegeometry.h \
    spaceshipgeometry.h \
    reactorparticle.h \
    spaceship.h \
    core.h \
    explosionparticle.h \
    text.h \
    menu.h \
    fbomultisample.h \
    sprite.h

DISTFILES += \
    ../release/Data/Shaders/background.fsh \
    ../release/Data/Shaders/cube.fsh \
    ../release/Data/Shaders/plane.fsh \
    ../release/Data/Shaders/shadow.fsh \
    ../release/Data/Shaders/spaceship.fsh \
    ../release/Data/Shaders/background.vsh \
    ../release/Data/Shaders/cube.vsh \
    ../release/Data/Shaders/plane.vsh \
    ../release/Data/Shaders/shadow.vsh \
    ../release/Data/Shaders/spaceship.vsh \
    ../release/Data/Shaders/reactor.fsh \
    ../release/Data/Shaders/reactor.vsh \
    ../release/Data/Shaders/text.fsh \
    ../release/Data/Shaders/text.vsh \
    ../release/Data/Shaders/scrolltext.fsh \
    ../release/Data/Shaders/scrolltext.vsh \
    ../release/Data/Shaders/postFX.fsh \
    ../release/Data/Shaders/postFX.vsh \
    ../release/Data/Shaders/finalFX.fsh \
    ../release/Data/Shaders/finalFX.vsh \
    ../release/Data/Shaders/sprite.vsh \
    ../release/Data/Shaders/sprite.fsh


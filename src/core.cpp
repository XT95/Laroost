#include <cmath>
#include "core.h"

Core Core::m_instance=Core();
Core::Core()
{

}

Core::~Core()
{

}

Core& Core::instance()
{
    return m_instance;
}

void Core::init()
{
    shaderText.load("Data/Shaders/text.vsh", NULL, "Data/Shaders/text.fsh");
    font.load("Data/Imgs/font.png");
    reset();

    score = 0.;
    highscore = 0.;
    rank = 1.;
}

void Core::reset()
{
    mode = CORE_MENU;
    score = 0;
    level = -1;
    speed = 30.f;
    time = 0.f;
    offset = 0.;
    fade = 1.;
    showSpeedUp = false;
}
void Core::play()
{
    reset();
    mode = CORE_PLAYING;
}

void Core::updateScore()
{
    highscore = fmax(score, highscore);
}

void Core::update(float elapsed)
{
    score += speed*elapsed*.25f;
    time += elapsed;
}

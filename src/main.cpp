#define GLEW_STATIC
#include <windows.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>
#include "demo.h"

static int width = 1280;
static int height = 720;


int main(int argc, char *argv[])
{
    SDL_Window *mainwindow;
    SDL_GLContext maincontext;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cout << "Unable to initialize SDL";
      return 1;
    }

    // Request opengl 4.4 or opengl es context
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Turn on double buffering with a 24bit Z buffer.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // MSAA
//    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
//    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,32);

    // Create the window
    mainwindow = SDL_CreateWindow("/_\\ Laroost", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN );

    SDL_ShowCursor(SDL_DISABLE);

    if(!mainwindow)
    {
       std::cout << "SDL Error: " << SDL_GetError() << std::endl;
       SDL_Quit();
       return 1;
    }

    // Create our opengl context and attach it to our window
    maincontext = SDL_GL_CreateContext(mainwindow);

    GLenum rev;
    glewExperimental = GL_TRUE;
    rev = glewInit();

    if(GLEW_OK != rev)
    {
        std::cout << "Error: " << glewGetErrorString(rev) << std::endl;
        return 1;
    }

    SDL_GL_SetSwapInterval(1);


    //Demo
    Demo *demo = new Demo(width, height);
    demo->init();


    //Event
    bool left=false,right=false,space=false;
    SDL_Event event;


    //Game loop :).
    bool loop=true;
    int currentTime,lastTime=0;
    while(loop)
    {
        currentTime = SDL_GetTicks();
        float elapsed = float(currentTime-lastTime)/1000.f;
        lastTime = currentTime;

        demo->update(elapsed, ((int)left)*-1+right, space);
        demo->render();
        SDL_GL_SwapWindow(mainwindow);

        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                  loop = false;
            }
            else if(event.type ==SDL_WINDOWEVENT)
            {
                if(event.window.event = SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    int w,h;
                    SDL_GetWindowSize(mainwindow,&w,&h);
                    //std::cout << w << " | " << h << std::endl;
                    demo->resize(w,h);
//                    Reshape(w,h);
                }
            }
            else if( event.type == SDL_KEYDOWN)
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    loop = false;
                    break;
                case SDLK_LEFT:
                    left = true;
                    break;
                case SDLK_RIGHT:
                    right = true;
                    break;
                case SDLK_k:
                    left = true;
                    break;
                case SDLK_m:
                    right = true;
                    break;
                case SDLK_SPACE:
                    space = true;
                    break;
            }
            else if( event.type == SDL_KEYUP)
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    left = false;
                    break;
                case SDLK_RIGHT:
                    right = false;
                    break;
                case SDLK_k:
                    left = false;
                    break;
                case SDLK_m:
                    right = false;
                    break;
                case SDLK_SPACE:
                    space = false;
                    break;
            }
        }
    }

    delete demo;

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    return 0;
}

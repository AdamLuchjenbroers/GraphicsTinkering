#pragma once


#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glcorearb.h>
#include <GL/glu.h>

#include "FrameworkOneApp.h"

class SDLDisplay  {
  public: 
    SDLDisplay(const char *title, int width, int height);
    virtual ~SDLDisplay();

    virtual void swapBuffers();
    virtual void mainLoop(FrameworkOneApp &app);
    virtual void close();

    void printRendererInfo();

  protected:
    int width, height;

  private:
    SDL_Window *app_window;
    SDL_GLContext app_glcontext;
};

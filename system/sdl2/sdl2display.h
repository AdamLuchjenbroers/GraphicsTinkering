#pragma once

#include <stdio.h>
#include "SDL2/SDL.h"
#include "GL/glcorearb.h"
#include "system/display.h"


class SDLDisplay : public DisplayInterface {
  public: 
    SDLDisplay(const char *title, int width, int height);
    ~SDLDisplay();

    virtual void swapBuffers();
    virtual void mainLoop(EngineApplication &app);
    virtual void close();

    void printRendererInfo();

  private:
    SDL_Window *app_window;
    SDL_GLContext app_glcontext;
};

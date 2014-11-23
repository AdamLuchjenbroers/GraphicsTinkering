#pragma once

#include <stdio.h>
#include "SDL2/SDL.h"
#include "GL/gl.h"


class SDLDisplay {
  public: 
    SDLDisplay(const char *title, int width, int height);
    ~SDLDisplay();

    void swapBuffers();

  private:
    SDL_Window *app_window;
    SDL_GLContext app_glcontext;
};

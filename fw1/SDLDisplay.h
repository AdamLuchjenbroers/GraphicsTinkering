#pragma once


#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glcorearb.h>
#include <GL/glu.h>
#include <string>

#include "FrameworkOneApp.h"

class SDLDisplay  {
    public: 
        virtual ~SDLDisplay();

        virtual void swapBuffers();
        virtual void mainLoop(FrameworkOneApp &app);
        virtual void close();

        std::string printable();
        void logRendererInfo();

        static SDLDisplay *basicDisplay(const char *title, int width, int heigth);
    protected:
        int width, height;
        SDLDisplay(const char *title, int width, int height);

    private:
        SDL_Window *app_window;
        SDL_GLContext app_glcontext;
};

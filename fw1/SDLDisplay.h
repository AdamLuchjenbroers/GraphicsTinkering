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

    /** Swap front and back display buffers */
    virtual void swapBuffers();
    /** Process any SDL events as part of the main loop and call the appropriate
        callback method in the main application to process them.
        @param app A reference to the application object.*/
    virtual void mainLoop(FrameworkOneApp &app);
    /** Close the current window */
    virtual void close();

    /** Returns a string containing details of the underlying OpenGL context
      * @return The version numbers and renderer details of the underlying OpenGL context
      */
    std::string printable();
    /** Print out the OpenGL renderer details to the log */
    void logRendererInfo();

    /** Creates an SDLDisplay in a basic, non-resizable window */
    static SDLDisplay *basicDisplay(const char *title, int width, int heigth);
protected:
    int _width, _height, _offsetX, _offsetY;
    char _title[64];

    SDLDisplay();

    bool createWindow();
private:
    SDL_Window *app_window;
    SDL_GLContext app_glcontext;
};

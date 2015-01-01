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

    /** Sets whether the window is resizable. Only effective before window creation 
      * @param resize Whether the window should be resizable.
      */
    void setResizable(bool resize);

    /** Queries the current window to determine if it is resizable.
      * @return True if the display window is resizable
      */
    bool isResizable();

    /** Calculates the aspect ratio of the current window 
      * @return The aspect ratio of the current display
      */
    inline GLfloat aspectRatio() {
        return ((GLfloat) _width / (GLfloat) _height);
    }

    /** Calculates the normalized device coordinates for a given pixel position
      * on screen (z is assumed to be 0, and is omitted)
      * @param[in] pixelX the X pixel position.
      * @param[in] pixelY the Y pixel position.
      * @param[out] ndcX the X position in normalised device coordinates.
      * @param[out] ndcY the Y position in normalised device coordinates.
      */
    inline void toNDC(int pixelX, int pixelY, GLfloat &ndcX, GLfloat &ndcY) {
        ndcX =  ((pixelX * 2.0) / _width)  - 1.0f;
        ndcY = -((pixelY * 2.0) / _height) + 1.0f;
    }

    /** Creates an SDLDisplay in a basic, non-resizable window */
    static SDLDisplay *basicDisplay(const char *title, int width, int height);

    /** Creates an SDLDisplay in a basic, resizable window */
    static SDLDisplay *resizableDisplay(const char *title, int width, int height, bool coreProfile);
    static SDLDisplay *resizableDisplay(const char *title, int width, int height);
protected:
    int _width, _height, _offsetX, _offsetY;
    Uint32 _sdlFlags;

    char _title[64];

    SDLDisplay();

    bool createWindow(bool coreProfile);
private:
    SDL_Window *app_window;
    SDL_GLContext app_glcontext;

    void processWindowEvent(SDL_WindowEvent &winEvent, FrameworkOneApp &app);
};

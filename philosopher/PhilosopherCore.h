#pragma once

#include "../fw1/fw1.h"
#include "../math/Matrix4.h"
#include "TableState.h"

#include <SDL2/SDL.h>

class PhilosopherCore : public FrameworkOneApp {
public:
   PhilosopherCore();
   ~PhilosopherCore();

   bool appMain();

   void appInit();

   void resizeWindow(int newX, int newY); 
   void keyEvent(SDL_Keysym &key, bool press);

   // FIXME: Scaffolding, remove when no longer needed
   TableState tableState = TableState(7);

protected:
    bool _running;
    GLfloat _angle;

    SDLDisplay *display;
    Matrix4 _projection;

    ShaderProgram _shader;
    GLuint _vertexarray;
};

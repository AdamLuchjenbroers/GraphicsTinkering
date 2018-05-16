#pragma once

#include "../fw1/fw1.h"
#include "../math/Matrix4.h"
#include "TableState.h"

class PhilosopherCore : public FrameworkOneApp {
public:
   PhilosopherCore();

   bool appMain();

   void appInit();

   void resizeWindow(int newX, int newY); 

   // FIXME: Scaffolding, remove when no longer needed
   TableState tableState = TableState(5);

protected:
    bool _running;

    SDLDisplay *display;
    Matrix4 _projection;

    ShaderProgram _shader;
};

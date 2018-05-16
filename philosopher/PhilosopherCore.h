#pragma once

#include "../fw1/fw1.h"
#include "../math/Matrix4.h"

class PhilosopherCore : public FrameworkOneApp {
public:
   PhilosopherCore();

   bool appMain();

   void appInit();

   void resizeWindow(int newX, int newY); 

protected:
    SDLDisplay *display;
    Matrix4 _projection;
};

#pragma once

#include "../fw1/fw1.h"
#include "../math/Matrix4.h"

#include "constants.h"

#include "Chopstick.h"
#include "Philosopher.h"
#include "PhilosopherRef.h"
#include "TableState.h"
#include "NaiveTable.h"

#include <SDL2/SDL.h>

class PhilosopherCore : public FrameworkOneApp {
public:
   PhilosopherCore();
   ~PhilosopherCore();

   bool appMain();

   void appInit();

   void resizeWindow(int newX, int newY); 
   void keyEvent(SDL_Keysym &key, bool press);

protected:
    GLfloat _angle;

    SDLDisplay *display;
    Matrix4 _projection;

    ShaderProgram _shader;
    GLuint _vertexarray;
    GLuint _buffer;

    TextureRef _tx_philosopher;
    TextureRef _tx_chopstick;

    virtual void setupTable(int diners);

    void updateTable();
    bool checkGLError(const char *errfmt, Logger::Level loglevel);

    TableState *_table = NULL;
};

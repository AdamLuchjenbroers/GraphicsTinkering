/*
 * Really basic shader from OpenGL SuperBible, chapter 2
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"


#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class SB6_Chapter2 : public SB6_BasicApp {
public:
    SB6_Chapter2();
    ~SB6_Chapter2();

    bool appMain();
    void appInit();

private:
    GLuint vertexarray;

    GLfloat pointsize;
    bool ascending;

};

SB6_Chapter2::SB6_Chapter2() {
   display = new SDLDisplay("Chapter 2 - A Point", 300, 400);
   running = true;

   pointsize = 10.0f;
   ascending = true;
}

SB6_Chapter2::~SB6_Chapter2() {
   if (display != NULL) {
       delete display;
   }

   delete vertex;
   delete fragment;
}

void SB6_Chapter2::appInit() {
    loadShaders("sb2-vertex.sdr", "sb2.fragment.sdr");
   
    glGenVertexArrays(1, &vertexarray);
}

bool SB6_Chapter2::appMain() {
    GLenum glerror;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vertexarray);
    glUseProgram(program);
    glPointSize(pointsize);

    glDrawArrays(GL_POINTS, 0, 1);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered while drawing: %s\n", gluErrorString(glerror));
    } 
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    if (ascending) {
        pointsize += 0.5f;

        if (pointsize >= 64.0f) {
            ascending = false;
        }
    } else {
        pointsize -= 0.5f;

        if (pointsize <= 0.5f) {
            ascending = true;
        }
    }

    return running;
}



int main( int argc, char* args[] ) { 
  EngineApplication *thisApp = new SB6_Chapter2();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

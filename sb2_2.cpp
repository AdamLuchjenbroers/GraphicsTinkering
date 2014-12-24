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

    bool appMain();
    void appInit();

private:
    GLuint vertexarray;
};

SB6_Chapter2::SB6_Chapter2() {
   display = SDLDisplay::basicDisplay("Chapter 2.2 - A Triangle", 300, 400);
   running = true;
}

void SB6_Chapter2::appInit() {
    loadVFProgram("sb2_2-vertex.sdr", "sb2-fragment.sdr");

    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
}

bool SB6_Chapter2::appMain() {
    GLenum glerror;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
       printf("ERROR: Error encountered while drawing: %s\n", gluErrorString(glerror));
    } 
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    return running;
}

int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new SB6_Chapter2();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

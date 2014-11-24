/*
 * Really basic shader from OpenGL SuperBible, chapter 2
 */

#include "system/sdl2/sdl2display.h"
#include "system/display.h"
#include "system/application.h"
#include "utilities/shader.h"

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class SB6_Chapter2 : public EngineApplication {
public:
    SB6_Chapter2();
    ~SB6_Chapter2();

    bool appMain();
    void appInit();
    void appQuit();

private:
    DisplayInterface *display;

    GLuint program, vertexarray;
    Shader *vertex, *fragment;

    bool running;
};

SB6_Chapter2::SB6_Chapter2() {
   this->display = NULL;
   this->running = true;

   this->vertex = new Shader("shader/sb2-vertex.sdr", GL_VERTEX_SHADER);
   this->fragment = new Shader("shader/sb2-fragment.sdr", GL_FRAGMENT_SHADER);

   this->program = glCreateProgram();
   glAttachShader(this->program, this->vertex->getShader());
   glAttachShader(this->program, this->fragment->getShader());
   glLinkProgram(this->program);

   glGenVertexArrays(1, &this->vertexarray);
   glBindVertexArray(this->vertexarray);
}

SB6_Chapter2::~SB6_Chapter2() {
   if (this->display != NULL) {
       delete this->display;
   }

   delete this->vertex;
   delete this->fragment;
}

void SB6_Chapter2::appInit() {
	this->display = new SDLDisplay("Chapter 2 - A Point", 300, 400);

}

bool SB6_Chapter2::appMain() {
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(this->program);
    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 0, 1);

    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(100);
    return this->running;
}

void SB6_Chapter2::appQuit() {
    this->running = false;
}



int main( int argc, char* args[] ) { 
  EngineApplication *thisApp = new SB6_Chapter2();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

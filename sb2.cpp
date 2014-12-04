/*
 * Really basic shader from OpenGL SuperBible, chapter 2
 */

#include "fw1/fw1.h"

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

    GLfloat pointsize;
    bool ascending;

};


SB6_Chapter2::SB6_Chapter2() {
   display = new SDLDisplay("Chapter 2 - A Point", 300, 400);
   running = true;

   vertex = NULL;
   fragment = NULL;

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
    ShaderLibrary *lib;
    GLuint glerror;
    char shaderPath[9] = "./shader";

    ShaderLibrary::setLibraryPath(shaderPath);
    lib = ShaderLibrary::getLibrary();

    vertex = lib->getShader("sb2-vertex.sdr", GL_VERTEX_SHADER); 
    fragment = lib->getShader("sb2-fragment.sdr", GL_FRAGMENT_SHADER); 
    
    program = glCreateProgram();
    glAttachShader(program, vertex->getShader());
    glAttachShader(program, fragment->getShader());
    glLinkProgram(program);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
         Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));
    } 
   
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

void SB6_Chapter2::appQuit() {
    running = false;
}



int main( int argc, char* args[] ) { 
  EngineApplication *thisApp = new SB6_Chapter2();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

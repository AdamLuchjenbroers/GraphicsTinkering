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


class SB6_Chapter3 : public EngineApplication {
public:
    SB6_Chapter3();
    ~SB6_Chapter3();

    bool appMain();
    void appInit();
    void appQuit();

private:
    DisplayInterface *display;

    GLuint program, vertexarray;
    Shader *vertex, *fragment;

    bool running;

    GLfloat offset_x, offset_y;
    bool increase_x, increase_y;

    void adjustOffset(GLfloat &offset, GLfloat increment, bool &increase);

};

SB6_Chapter3::SB6_Chapter3() {
   GLenum glerror;

   display = new SDLDisplay("Chapter 2 - A Point", 300, 400);
   running = true;

   vertex = new Shader("shader/sb3_1-vertex.sdr", GL_VERTEX_SHADER);
   printf("Vertex Shader Loaded\n------------\n");
   vertex->printShader();
   printf("------------\n");

   fragment = new Shader("shader/sb2-fragment.sdr", GL_FRAGMENT_SHADER);
   printf("Fragment Shader Loaded\n------------\n");
   fragment->printShader();
   printf("------------\n");

   program = glCreateProgram();
   glAttachShader(program, vertex->getShader());
   glAttachShader(program, fragment->getShader());
   glLinkProgram(program);
   glerror = glGetError();
   if (glerror != GL_NO_ERROR) {
     printf("ERROR: Unable to link rendering program: %s\n", gluErrorString(glerror));
   } 

   glGenVertexArrays(1, &vertexarray);

   offset_x = 0.0f;
   increase_x = true;
   offset_y = 0.0f;
   increase_y = true;
}

SB6_Chapter3::~SB6_Chapter3() {
   if (display != NULL) {
       delete display;
   }

   delete vertex;
   delete fragment;
}

void SB6_Chapter3::appInit() {
}

void SB6_Chapter3::adjustOffset(GLfloat &offset, GLfloat increment, bool &increase) {
    if (increase) {
        offset += increment;
    } else {
        offset -= increment;
    }

    if (offset >= 0.8f || offset <= -0.8f) {
        increase = !increase;
    }

}

bool SB6_Chapter3::appMain() {
    GLenum glerror;
    GLfloat offset[] = { offset_x, offset_y, 0.0f, 0.0f };
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vertexarray);
    glUseProgram(program);

    glVertexAttrib4fv(0, offset);
    if (glerror != GL_NO_ERROR) {
       printf("ERROR: Error encountered while calling glVertexAttrib4fv: %s\n", gluErrorString(glerror));
    }
    display->swapBuffers();
    glDrawArrays(GL_TRIANGLES, 0, 3);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
       printf("ERROR: Error encountered while calling glDrawArrays: %s\n", gluErrorString(glerror));
    } 
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    adjustOffset(offset_x, 0.1f, increase_x);
    adjustOffset(offset_y, 0.07f, increase_y);

    return running;
}

void SB6_Chapter3::appQuit() {
    running = false;
}



int main( int argc, char* args[] ) { 
  EngineApplication *thisApp = new SB6_Chapter3();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

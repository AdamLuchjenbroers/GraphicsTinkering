/*
 * Really basic shader from OpenGL SuperBible, chapter 2
 */

#include "fw1/fw1.h"

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

    GLfloat offset_x, offset_y, time;
    bool increase_x, increase_y, increase_time;

    void adjustOffset(GLfloat &offset, GLfloat increment, bool &increase, GLfloat min, GLfloat max);
    void colour_for_time(GLfloat *colour);

};

SB6_Chapter3::SB6_Chapter3() {
   GLenum glerror;

   display = new SDLDisplay("Chapter 2 - A Point", 300, 400);
   running = true;

   vertex = new Shader("shader/sb3_2-vertex.sdr", GL_VERTEX_SHADER);
   fragment = new Shader("shader/sb3-fragment.sdr", GL_FRAGMENT_SHADER);

   program = glCreateProgram();
   glAttachShader(program, vertex->getShader());
   glAttachShader(program, fragment->getShader());
   glLinkProgram(program);
   glerror = glGetError();
   if (glerror != GL_NO_ERROR) {
     Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));
   } 

   glGenVertexArrays(1, &vertexarray);

   offset_x = 0.0f;
   increase_x = true;

   offset_y = 0.0f;
   increase_y = true;

   time = 0.0f;
   increase_time = true;
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

void SB6_Chapter3::adjustOffset(GLfloat &offset, GLfloat increment, bool &increase, GLfloat min, GLfloat max) {
    if (increase) {
        offset += increment;
    } else {
        offset -= increment;
    }

    if (offset >= max || offset <= min) {
        increase = !increase;
    }

}

bool SB6_Chapter3::appMain() {
    GLenum glerror;
    GLfloat offset[] = { offset_x, offset_y, 0.0f, 0.0f };
    GLfloat colour[4];
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vertexarray);
    glUseProgram(program);

    colour_for_time(colour);

    glVertexAttrib4fv(0, offset);
    glVertexAttrib4fv(1, colour);
    if (glerror != GL_NO_ERROR) {
       Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered while calling glVertexAttrib4fv: %s\n", gluErrorString(glerror));
    }
    display->swapBuffers();
    glDrawArrays(GL_TRIANGLES, 0, 3);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
       Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered while calling glDrawArrays: %s\n", gluErrorString(glerror));
    } 
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    adjustOffset(offset_x, 0.02f, increase_x, -0.8f, 0.8f);
    adjustOffset(offset_y, 0.015f, increase_y, -0.8f, 0.8f);
    adjustOffset(time, 1.0f, increase_time, 0.0f, 512.0f );

    return running;
}

void SB6_Chapter3::appQuit() {
    running = false;
}

void SB6_Chapter3::colour_for_time(GLfloat *colour) {
    if ( time >= 256 ) {
      colour[COLOUR_RED] = (512 - time) / 256.0f;
    } else {
      colour[COLOUR_RED] = time / 256.0f;
    };

    if ( time >= 256 ) {
      colour[COLOUR_GREEN] = (time - 256) / 256.0f;
    } else {
      colour[COLOUR_GREEN] = 0.0f;
    };
    if ( time >= 256 ) {
      colour[COLOUR_BLUE] = 0.0f;
    } else {
      colour[COLOUR_BLUE] = (256 - time) / 256.0f;
    };

    colour[COLOUR_ALPHA] = 1.0f;

}


int main( int argc, char* args[] ) { 
  EngineApplication *thisApp = new SB6_Chapter3();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

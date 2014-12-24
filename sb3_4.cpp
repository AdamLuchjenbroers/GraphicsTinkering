/*
 * Basic tesselation shaders from chapter 3
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class SB6_Chapter3 : public SB6_BasicApp {
public:
    SB6_Chapter3();

    bool appMain();
    void appInit();

    void keyEvent(SDL_Keysym &key, bool press);

private:
    GLuint vertexarray;

    GLfloat offset_x, offset_y, time, tess_lvl;
    bool increase_x, increase_y, increase_time;

    void colour_for_time(GLfloat *colour);
};

SB6_Chapter3::SB6_Chapter3() {
   display = SDLDisplay::basicDisplay("Chapter 3 - Tesselation", 600, 600);
   running = true;

   offset_x = 0.0f;
   increase_x = true;

   offset_y = 0.0f;
   increase_y = true;

   time = 0.0f;
   increase_time = true;

   tess_lvl = 4.0f;

   vertexarray = 0;
}

void SB6_Chapter3::appInit() {
    GLenum glerror;

    loadShader("sb3_4-vertex.sdr", GL_VERTEX_SHADER);
    loadShader("sb3_3-fragment.sdr", GL_FRAGMENT_SHADER);
    loadShader("sb3_4-tcs.sdr", GL_TESS_CONTROL_SHADER);
    loadShader("sb3_4-tes.sdr", GL_TESS_EVALUATION_SHADER);

    linkProgram();

    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glEnable(GL_LINE_SMOOTH);

    glUseProgram(program.programID());

    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered in appInit(): %s\n", gluErrorString(glerror));
    }
}


bool SB6_Chapter3::appMain() {
    GLenum glerror;
    GLfloat offset[] = { offset_x, offset_y, 0.0f, 0.0f };
    GLfloat colour[4];

    colour_for_time(colour);

    glClearColor(1.0f - colour[0], 1.0f - colour[1], 1.0f - colour[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glVertexAttrib4fv(0, colour);
    glVertexAttrib1f(1, tess_lvl);

    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
       Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered while calling glVertexAttrib4fv: %s\n", gluErrorString(glerror));
    }

    glDrawArrays(GL_PATCHES, 0, 3);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
       Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered while calling glDrawArrays: %s\n", gluErrorString(glerror));
    } 
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    valueSwing(offset_x, 0.02f, increase_x, -0.8f, 0.8f);
    valueSwing(offset_y, 0.015f, increase_y, -0.8f, 0.8f);
    valueSwing(time, 1.0f, increase_time, 0.0f, 512.0f );

    return running;
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

void SB6_Chapter3::keyEvent(SDL_Keysym &key, bool press) {
    if ((key.sym == SDLK_KP_MINUS || key.sym == SDLK_MINUS) && tess_lvl > 1.0f) {
        tess_lvl -= 1.0f;
    }

    if (key.sym == SDLK_KP_PLUS || key.sym == SDLK_PLUS) {
        tess_lvl += 1.0f;
    }
}

int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new SB6_Chapter3();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

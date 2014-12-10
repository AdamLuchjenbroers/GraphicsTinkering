/*
 * Really basic shader from OpenGL SuperBible, chapter 3
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

private:
    GLuint vertexarray;

    GLfloat offset_x, offset_y;
    bool increase_x, increase_y;
};

SB6_Chapter3::SB6_Chapter3() {
   display = new SDLDisplay("Chapter 3 - Moving Triangle", 300, 400);
   running = true;

   offset_x = 0.0f;
   increase_x = true;
   offset_y = 0.0f;
   increase_y = true;

   vertexarray = 0;
}

void SB6_Chapter3::appInit() {
    GLuint glerror;
    bool success;

    ShaderLibrary::setLibraryPath("./shader");

    success = program.addShader("sb3_1-vertex.sdr", GL_VERTEX_SHADER);
    success &= program.addShader("sb3-fragment.sdr", GL_FRAGMENT_SHADER);

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");
        exit(1);
    }

    program.bindAttribute("offset", 0);
    program.bindAttribute("color", 1);

    success = program.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));
        exit(1);
    }
    
    glUseProgram(program.programID());

    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
}

bool SB6_Chapter3::appMain() {
    GLenum glerror;
    GLfloat offset[] = { offset_x, offset_y, 0.0f, 0.0f };
    GLint offsetLocation;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    offsetLocation = glGetAttribLocation(program.programID(), "offset");

    //printf("[%1.4f, %1.4f, %1.4f, %1.4f]\n", offset[0], offset[1], offset[2], offset[3]); 
    
    glVertexAttrib4f(0, 1.0f, 1.0f, 0.0f, 0.0f);
    if (glerror != GL_NO_ERROR) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered while calling glVertexAttrib4fv: %s\n", gluErrorString(glerror));
    }
    glDrawArrays(GL_TRIANGLES, 0, 3);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
         Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Error encountered while calling glDrawArrays: %s\n", gluErrorString(glerror));
    } 
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    valueSwing(offset_x, 0.02f, increase_x, -1.0f, 1.0f);
    valueSwing(offset_y, 0.015f, increase_y, -1.0f, 1.0f);

    return running;
}


int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new SB6_Chapter3();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

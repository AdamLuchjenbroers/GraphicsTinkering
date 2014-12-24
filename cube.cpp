/*
 * Really basic shader from OpenGL SuperBible, chapter 3
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"

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
    GLuint vertexarray, vertexbuffer, colourbuffer;

    Matrix4 _projection;

    GLfloat angle;
};

SB6_Chapter3::SB6_Chapter3() {
   display = SDLDisplay::basicDisplay("Spinning Cube", 400, 400);
   running = true;

   angle = 0.0f;   

   vertexarray = 0;

   _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

static const float vertices[] =
{
     1.0f,  1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f,
};

static const float colours[] =
{
     0.8f, 0.2f, 0.2f, 1.0f,
     0.8f, 0.2f, 0.2f, 1.0f,
     0.8f, 0.2f, 0.2f, 1.0f,
     0.8f, 0.2f, 0.2f, 1.0f,
     0.8f, 0.2f, 0.2f, 1.0f,
     0.8f, 0.2f, 0.2f, 1.0f,
     0.2f, 0.8f, 0.2f, 1.0f,
     0.2f, 0.8f, 0.2f, 1.0f,
     0.2f, 0.8f, 0.2f, 1.0f,
     0.2f, 0.8f, 0.2f, 1.0f,
     0.2f, 0.8f, 0.2f, 1.0f,
     0.2f, 0.8f, 0.2f, 1.0f,
     0.2f, 0.2f, 0.8f, 1.0f,
     0.2f, 0.2f, 0.8f, 1.0f,
     0.2f, 0.2f, 0.8f, 1.0f,
     0.2f, 0.2f, 0.8f, 1.0f,
     0.2f, 0.2f, 0.8f, 1.0f,
     0.2f, 0.2f, 0.8f, 1.0f,
     0.8f, 0.2f, 0.8f, 1.0f,
     0.8f, 0.2f, 0.8f, 1.0f,
     0.8f, 0.2f, 0.8f, 1.0f,
     0.8f, 0.2f, 0.8f, 1.0f,
     0.8f, 0.2f, 0.8f, 1.0f,
     0.8f, 0.2f, 0.8f, 1.0f,
     0.2f, 0.8f, 0.8f, 1.0f,
     0.2f, 0.8f, 0.8f, 1.0f,
     0.2f, 0.8f, 0.8f, 1.0f,
     0.2f, 0.8f, 0.8f, 1.0f,
     0.2f, 0.8f, 0.8f, 1.0f,
     0.2f, 0.8f, 0.8f, 1.0f,
     0.8f, 0.8f, 0.2f, 1.0f,
     0.8f, 0.8f, 0.2f, 1.0f,
     0.8f, 0.8f, 0.2f, 1.0f,
     0.8f, 0.8f, 0.2f, 1.0f,
     0.8f, 0.8f, 0.2f, 1.0f,
     0.8f, 0.8f, 0.2f, 1.0f,
};

void SB6_Chapter3::appInit() {
    loadVFProgram("cube.sdr", "sb3-fragment.sdr");

    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
    checkGLError("Error encountered creating Vertex Array: %s\n", Logger::LOG_ERROR);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    checkGLError("Error encountered creating Vertex Array Buffer: %s\n", Logger::LOG_ERROR);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    checkGLError("Error encountered loading Vertex Array Buffer: %s\n", Logger::LOG_ERROR);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    checkGLError("Error encountered preparing Vertex Data: %s\n", Logger::LOG_ERROR);

    glGenBuffers(1, &colourbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
    checkGLError("Error encountered creating Colour Array Buffer: %s\n", Logger::LOG_ERROR);

    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colours), colours);
    checkGLError("Error encountered loading Array Buffer: %s\n", Logger::LOG_ERROR);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);
    checkGLError("Error encountered preparing Vertex Data: %s\n", Logger::LOG_ERROR);

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());

    glEnable(GL_DEPTH_TEST);
    checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}

bool SB6_Chapter3::appMain() {
    GLenum glerror;
    GLint offsetLocation;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint xform_loc = program.uniformLocation("xform");
    Matrix4 translate = Matrix4::translate(0.0f, 0.0f, 4.0f);
    Matrix4 rotate = Matrix4::rotate(angle / 2.0f, angle, 0.0f); 

    Matrix4 xform = translate * rotate;

    glUniformMatrix4fv(xform_loc, 1, false, xform.buffer());
  
    checkGLError("Error encountered while calling glVertexAttrib4fv: %s\n", Logger::LOG_ERROR);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    checkGLError("Error encountered while calling glDrawArrays: %s\n", Logger::LOG_ERROR);
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    angle += 0.5f;
    if (angle >= 720.0f) {
        angle -= 720.0f;
    }

    return running;
}


int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new SB6_Chapter3();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}

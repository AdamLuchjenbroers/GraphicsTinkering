/*
 * Spinning cube.
 */

#include "CubeApp.h"

#include <iostream>

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class BasicCube : public CubeApp {
public:
    BasicCube();

    void appInit();

private:
    GLuint colourbuffer;
};

BasicCube::BasicCube() {
    display = SDLDisplay::resizableDisplay("Spinning Cube", 400, 400);

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

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

void BasicCube::appInit() {
    bool shaderReady = loadVFProgram("cube.sdr", "zshade-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    CubeApp::appInit();

    glGenBuffers(1, &colourbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
    checkGLError("Error encountered creating Colour Array Buffer: %s\n", Logger::LOG_ERROR);

    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colours), colours);
    checkGLError("Error encountered loading Colour Array Buffer: %s\n", Logger::LOG_ERROR);

    glVertexAttribPointer(VI_COLOR, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(VI_COLOR);
    checkGLError("Error encountered preparing Vertex Colour Data: %s\n", Logger::LOG_ERROR);

}

int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new BasicCube();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
